#include "NESIncludes.h"
#include <iostream>
#include <iomanip>
#include "Debugger.h"

void debug(R6502 * cpu);
uint8_t test(R6502& cpu, Memory * mem);
uint8_t assertEqual(uint8_t expected, uint8_t actual);
uint8_t assertEqual(R6502::State expected, R6502::State actual);
void printExpectedAndActual(uint8_t expected, uint8_t actual);
void printInstruction(uint8_t opCode);

int main() {
  Memory * memory = new Memory();
  R6502 cpu = R6502(memory);
  cpu.powerOn();
  test(cpu, memory);
  //debug(&cpu);
}

void debug(R6502 * cpu) {
  ConsoleDebugger debugger = ConsoleDebugger(cpu);
  int i = 0;
  while (i < 10) {
    debugger.step();
    i++;
  }
}

void prepCPUForInstructionCyclesTest(uint8_t opCode, R6502& cpu, Memory * mem) {
  mem->write(0x0000, opCode);
  mem->write(0xFFFC, 0x00);
  mem->write(0xFFFD, 0x00);
  cpu.powerOn();
}

uint8_t testInstructionCycleAccuracy(R6502& cpu, Memory * mem, uint8_t opCode, uint8_t expectedMachineCycles) {
    std::cout << "Testing instruction cycles...\nIntruction: ";
    printInstruction(opCode);
    std::cout << std::endl;

    prepCPUForInstructionCyclesTest(opCode, cpu, mem);
    cpu.doNextInstruction();

    uint8_t extraCycles = cpu.getExtraCyclesPassedThisInstruction();
    return assertEqual(expectedMachineCycles + extraCycles, cpu.getCyclesPassedThisInstruction());
}

uint8_t testInstructionsCycleAccuracy(R6502& cpu, Memory * mem) {
  uint8_t expectedCycleCountMatrix[0x100] = {
        /* 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F  */
/* 0 */    7, 6, 0, 0, 0, 3, 5, 0, 3, 2, 2, 0, 0, 4, 6, 0, 
/* 1 */    2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0, 
/* 2 */    6, 6, 0, 0, 3, 3, 5, 0, 4, 2, 2, 0, 4, 4, 6, 0, 
/* 3 */    2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0, 
/* 4 */    6, 6, 0, 0, 0, 3, 5, 0, 3, 2, 2, 0, 3, 4, 6, 0, 
/* 5 */    2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0, 
/* 6 */    6, 6, 0, 0, 0, 3, 5, 0, 4, 2, 2, 0, 5, 4, 6, 0, 
/* 7 */    2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0, 
/* 8 */    0, 6, 0, 0, 3, 3, 3, 0, 2, 0, 2, 0, 4, 4, 4, 0, 
/* 9 */    2, 6, 0, 0, 4, 4, 4, 0, 2, 5, 2, 0, 0, 5, 0, 0, 
/* A */    2, 6, 2, 0, 3, 3, 3, 0, 2, 2, 2, 0, 4, 4, 4, 0, 
/* B */    2, 5, 0, 0, 4, 4, 4, 0, 2, 4, 2, 0, 4, 4, 4, 0, 
/* C */    2, 6, 0, 0, 3, 3, 5, 0, 2, 2, 2, 0, 4, 4, 6, 0, 
/* D */    2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0, 
/* E */    2, 6, 0, 0, 3, 3, 5, 0, 2, 2, 2, 0, 4, 4, 6, 0, 
/* F */    2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0 
  };

  std::cout << "Testing CPU cycle accuracy..." << std::endl;
  uint16_t opCode = 0;
  uint8_t testFailed = 0x00;
  while (opCode <= 0xFF && !testFailed) {
    uint8_t expectedMachineCycles = expectedCycleCountMatrix[opCode];
    if (expectedMachineCycles != 0) testFailed = !testInstructionCycleAccuracy(cpu, mem, opCode, expectedMachineCycles);
    opCode++;
  }

  return !testFailed;
}

void loadProgram() {

}

uint8_t testSimpleProgram(R6502& cpu, Memory * mem) {
  /*
    https://skilldrick.github.io/easy6502/

    LDA #$01
    sta $0200
    lda #$05
    sta $0201
    lda #$08
    sta $0202

    a9 01 8d 00 02 a9 05 8d 01 02 a9 08 8d 02 02 
  */

  std::cout << "Testing simple program..." << std::endl;

  const size_t progSize = 15;

  uint8_t prog[progSize] = {
    0xa9, 0x01, 0x8d, 0x00, 0x02,
    0xa9, 0x05, 0x8d, 0x01, 0x02,
    0xa9, 0x08, 0x8d, 0x02, 0x02,
  };

  unsigned int i = 0;
  for (i = 0; i < progSize; i++) {
    mem->write(i, prog[i]);
  }

  cpu.powerOn();
  ConsoleDebugger debugger = ConsoleDebugger(&cpu);

  std::cout << "Simple program initial state: " << std::endl;
  debugger.showState();

  while (cpu.getState().pc < progSize) {
    cpu.doNextInstruction();
  }

  std::cout << "Simple program end state: " << std::endl;
  debugger.showState();

  R6502::State actualState = cpu.getState();
  R6502::State expectedState = {
    0x08,
    0x00,
    0x00,
    0x000F,
    0xFD,
    0x34
  };

  return assertEqual(expectedState, actualState);
}

uint8_t test(R6502& cpu, Memory * mem) {
  // Load up test program. Returns true if success.

  if (testInstructionsCycleAccuracy(cpu, mem)) {
    std::cout << "Instruction cycle accuracy tests passed!" << std::endl;
  } else {
    std::cout << "Instruction cycle accuracy tests failed..." << std::endl;
    return 0x00;
  }

  if (testSimpleProgram(cpu, mem)) {
    std::cout << "Simple program tests passed!" << std::endl;
  } else {
    std::cout << "Simple program tests failed..." << std::endl;
    return 0x00;
  }

  std::cout << "All tests passed!" << std::endl;
  return 0x01;
}

uint8_t assertEqual(uint8_t expected, uint8_t actual) {
  if (expected != actual) {
    std::cout << "\tFailed!!!";
    std::cout << std::endl;
    printExpectedAndActual(expected, actual);
    std::cout << std::endl;

    return 0x00;
  }

  std::cout << "\tPassed" << std::endl;
  return 0x01;
}

uint8_t assertEqual(R6502::State expected, R6502::State actual) {
  if (
    expected.accumulator != actual.accumulator ||
    expected.x != actual.x ||
    expected.y != actual.y ||
    expected.pc != actual.pc ||
    expected.sp != actual.sp ||
    expected.P != actual.P
  ) {
    std::cout << "\tFailed!!!";
    std::cout << std::endl;

    return 0x00;
  }

  std::cout << "\tPassed" << std::endl;
  return 0x01;
}

void printExpectedAndActual(uint8_t expected, uint8_t actual) {
  std::cout
    << "Expected: " << (int) expected
    << " / Actual: " << (int) actual
    << std::endl;
}

void printInstruction(uint8_t opCode) {
  R6502::InstructionMetadata instructionMetadata = R6502::getInstructionMetadata(opCode);
  std::cout
    << "[0x"
    << std::uppercase <<  std::setw(2) << std::setfill('0') << std::hex << (int) opCode
    << "] OP: " << instructionMetadata.mnemonic
    << " / ADDR_MODE: " << instructionMetadata.addressModeName;
}