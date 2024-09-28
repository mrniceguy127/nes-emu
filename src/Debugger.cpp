#include "NESIncludes.h"
#include "Debugger.h"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <bitset>


// MAKE MODULE FOR THIS STUFF.... THIS FUNCTION ALREADY EXISTS IN MAIN.
static std::string getInstructionDisp(uint8_t opCode) {
  R6502::InstructionMetadata instructionMetadata = R6502::getInstructionMetadata(opCode);
  std::ostringstream instructionDisp;
  instructionDisp
    << "[" << instructionMetadata.mnemonic
    << "  " << std::setw(9) << std::setfill(' ') << std::left << instructionMetadata.addressModeName;
  instructionDisp << "]  "
    << "0x"
    << std::uppercase <<  std::setw(2) << std::setfill('0') << std::hex << (int) opCode;
  return instructionDisp.str();
}

static std::string getBinDisplay(uint16_t byte, int width) {
  std::ostringstream byteDisplay;
  byteDisplay << "0x" << std::uppercase << std::setw(width) << std::setfill('0') << std::hex << (int) byte;
  return byteDisplay.str();
}

static std::string getBinDisplay(uint8_t byte) {
  return getBinDisplay((uint16_t) byte, 2);
}

static std::string getBinDisplay(uint16_t doubleByte) {
  return getBinDisplay(doubleByte, 4);
}

std::string getProcessorStateDisplay(uint8_t P) {
    enum FLAGS { // Never considered using enums for bit manipulation. Credit to OneLoneCoder for this strategy.
      N = 0x01 << 7, // Negative?
      V = 0x01 << 6, // Overflow?
      U = 0x01 << 5, // UNUSED
      B = 0x01 << 4, // BRK command?
      D = 0x01 << 3, // Decimal mode?
      I = 0x01 << 2, // IRQ disable?
      Z = 0x01 << 1, // Result zero?
      C = 0x01 << 0  // Carry?
    };

    std::ostringstream disp;
    P & N ? disp << "N" : disp << "-";
    P & V ? disp << "V" : disp << "-";
    P & U ? disp << "U" : disp << "-";
    P & B ? disp << "B" : disp << "-";
    P & D ? disp << "D" : disp << "-";
    P & I ? disp << "I" : disp << "-";
    P & Z ? disp << "Z" : disp << "-";
    P & C ? disp << "C" : disp << "-";

    return disp.str();
}



Debugger::Debugger(R6502* c) : cpu(c) { }

void Debugger::step() {
  const size_t inputSize = 2;
  char inputBuffer[inputSize];  
  previousState = cpu->getState();
  cpu->doNextInstruction();
  R6502::State state = cpu->getState();

  if (state.pc == breakPoint && breakPointEnabled) hitBreak = 0x01;
  if (hitBreak) {
    outputHandler->step();
    showState();
    inputHandler->getStepInput(inputBuffer, inputSize);
  } else if (stackTraceEnabled) {
    showState();
  }

}

void Debugger::showState() {
  outputHandler->showState(cpu, previousState);
}

void Debugger::run() {
  while (true) {
    step();
  }
}

void Debugger::pause() {
  hitBreak = 0x01;
}

void Debugger::setBreakPoint(uint16_t bp) {
  breakPoint = bp;
  breakPointEnabled = 0x01;
}

void Debugger::enableStackTrace() {
  stackTraceEnabled = 0x01;
}

void DebuggerConsoleOuptutStrategy::step() {
  std::cout << "[STEP] ";
}



void DebuggerConsoleInputStrategy::getStepInput(char* inputBuffer, const size_t storeLength) {
  *inputBuffer = getchar();
  char c = '\0';
  if (*inputBuffer != '\n' && *inputBuffer != EOF) while ((c = getchar()) != '\n' && c != EOF);
  std::cout << "\033[F"    // Move cursor up one line
    << "\033[2K";  // Erase the entire line
}

void DebuggerConsoleOuptutStrategy::showState(R6502 * cpu, R6502::State previousState) {
  R6502::State state = cpu->getState();

  std::cout << getBinDisplay(previousState.pc) << ":   " << getInstructionDisp(cpu->getCurrentOpCode());
  const uint16_t pc = cpu->memory->read(state.pc);
  const uint8_t lastOperand = cpu->memory->read(previousState.pc + 1);
  std::cout
    << " " << getBinDisplay(lastOperand) << " *(->" << getBinDisplay(cpu->absAddr) << ") = " << getBinDisplay(cpu->operand)
    << "   A: " <<  getBinDisplay(state.accumulator)
    << " X: " <<  getBinDisplay(state.x)
    << " Y: " <<  getBinDisplay(state.y)
    << " PC: " << getBinDisplay(state.pc)
    << " SP: " << getBinDisplay(state.sp)
    << "   " <<  getProcessorStateDisplay(state.P)
  << std::endl;

  lastPC = state.pc;
}

ConsoleDebugger::ConsoleDebugger(R6502* c) : Debugger(c) {
  inputHandler = new DebuggerConsoleInputStrategy();
  outputHandler = new DebuggerConsoleOuptutStrategy();
}