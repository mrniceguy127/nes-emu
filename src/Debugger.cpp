#include "NESIncludes.h"
#include "Debugger.h"

#include <iostream>
#include <iomanip>
#include <bitset>


// MAKE MODULE FOR THIS STUFF.... THIS FUNCTION ALREADY EXISTS IN MAIN.
static void printInstruction(uint8_t opCode) {
  R6502::InstructionMetadata instructionMetadata = R6502::getInstructionMetadata(opCode);
  std::cout
    << "[0x"
    << std::uppercase <<  std::setw(2) << std::setfill('0') << std::hex << (int) opCode
    << "] OP: " << instructionMetadata.mnemonic
    << " / ADDR_MODE: " << instructionMetadata.addressModeName;
}



Debugger::Debugger(R6502* c) : cpu(c) { }

void Debugger::step() {
  const size_t inputSize = 2;
  char inputBuffer[inputSize];  
  inputHandler->getStepInput(inputBuffer, inputSize);
  cpu->doNextInstruction();
  showState();
}

void Debugger::showState() {
  outputHandler->showState(cpu);
}

void DebuggerConsoleInputStrategy::getStepInput(char* inputBuffer, const size_t storeLength) {
  std::cout << "Press enter to step next instruction" << std::endl;
  *inputBuffer = getchar();
  char c = '\0';
  if (*inputBuffer != '\n' && *inputBuffer != EOF) while ((c = getchar()) != '\n' && c != EOF);
}

void DebuggerConsoleOuptutStrategy::showState(R6502 * cpu) {
  R6502::State state = cpu->getState();

  std::bitset<8> processorStateDisp(state.P);

  std::cout << "<Instruction executed> ";
  printInstruction(cpu->getCurrentOpCode());
  const uint16_t pc = cpu->memory->read(state.pc);
  const uint8_t operand1 = cpu->memory->read(state.pc + 1);
  const uint8_t operand2 = cpu->memory->read(state.pc + 2);
  std::cout << std::endl;
  std::cout
    << "<REGISTERS STATE>" << std::endl
    << "Accumulator: " << std::hex << (int)      state.accumulator << std::endl
    << "X-Index: " << std::hex << (int)          state.x << std::endl
    << "Y-Index: " << std::hex << (int)          state.y << std::endl
    << "Program Counter: " << std::hex << (int)  state.pc << std::endl
    << "Operand 1: " << std::hex << (int)        operand1 << std::endl
    << "Operand 2: " << std::hex << (int)        operand2  << std::endl
    << "Stack Pointer: " << std::hex << (int)    state.sp << std::endl
    << "Processor State: " <<                    processorStateDisp
  << std::endl;
}

ConsoleDebugger::ConsoleDebugger(R6502* c) : Debugger(c) {
  inputHandler = new DebuggerConsoleInputStrategy();
  outputHandler = new DebuggerConsoleOuptutStrategy();
}