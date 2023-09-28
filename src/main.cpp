#include "NESIncludes.h"
#include <iostream>
#include <iomanip>

uint8_t test(R6502& cpu, Memory& memory);
void printInstruction(int instructionMatrixIndex);

int main() {
  Memory memory = Memory();
  R6502 cpu = R6502(memory);
  cpu.init();
  test(cpu, memory);
}

uint8_t testCycleAccuracy(R6502& cpu, Memory& memory) {
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
  const R6502::Instruction* instructionMatrix = R6502::getInstructionMatrix();

  R6502::Instruction instruction = R6502::NULL_INSTRUCTION;
  uint8_t expectedMachineCycles = 0;
  int i = 0;
  for (i = 0; i < R6502::getInstructionCount(); i++) {
    instruction = instructionMatrix[i];
    expectedMachineCycles = expectedCycleCountMatrix[i];
    if (instruction.operation != R6502::NULLOP) {
      std::cout << "Testing instruction cycles...\nIntruction: ";
      printInstruction(i);
      std::cout << std::endl;

      cpu.init();
      cpu.doInstruction(instruction);


      uint8_t extraCycles = cpu.getExtraCyclesPassedThisInstruction();
      if (cpu.getCyclesPassedThisInstruction() != expectedMachineCycles + extraCycles) {
        std::cout << "Failed instruction (incorrect amount of machine cycles): OP: ";
        printInstruction(i);
        std::cout << std::endl;
        std::cout
          << "Expected: " << (int) expectedMachineCycles + extraCycles
          << " / Actual: " << (int) cpu.getCyclesPassedThisInstruction()
          << std::endl;

        return 0x00;
      } else {
        std::cout << "\tPassed" << std::endl;
      }

      std::cout
        << std::endl;
    }
  }

  std::cout << "Instruction cycle accuracy tests passed!" << std::endl;
  return 0x01;
}



uint8_t test(R6502& cpu, Memory& memory) {
  // Load up test program. Returns true if success.
  //std::cout << "I do nothing yet! :D" << std::endl;
  if (testCycleAccuracy(cpu, memory)) {
    std::cout << "Tests passed!" << std::endl;
  } else {
    std::cout << "Tests failed..." << std::endl;
  }

  return 0x01;
}


void printInstruction(int instructionMatrixIndex) {
  R6502::Instruction instruction = R6502::getInstructionMatrix()[instructionMatrixIndex];
  R6502::InstructionMetadata instructionMetadata = R6502::getInstructionMetadata(instruction);
  std::cout
    << "[0x"
    << std::uppercase <<  std::setw(2) << std::setfill('0') << std::hex
    << instructionMatrixIndex
    << "] OP: "
    << instructionMetadata.mnemonic
    << " / ADDR_MODE: "
    << instructionMetadata.addressModeName;
}