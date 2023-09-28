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
  std::cout << "Testing cycles..." << std::endl;
  const R6502::Instruction* instructionMatrix = R6502::getInstructionMatrix();

  R6502::Instruction instruction = R6502::NULL_INSTRUCTION;
  int i = 0;
  for (i = 0; i < R6502::getInstructionCount(); i++) {
    instruction = instructionMatrix[i];
    if (instruction.operation != R6502::NULLOP) {
      std::cout << "Testing instruction cycles...\nIntruction: ";
      printInstruction(i);
      std::cout << std::endl;

      cpu.init();
      cpu.doInstruction(instruction);


      uint8_t extraCycles = cpu.getExtraCyclesPassedThisInstruction();
      if (cpu.getCyclesPassedThisInstruction() != instruction.machineCycles + extraCycles) {
        std::cout << "Failed instruction (incorrect amount of machine cycles): OP: ";
        printInstruction(i);
        std::cout << std::endl;
        std::cout
          << "Expected: " << (int) instruction.machineCycles + extraCycles
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
    << instructionMetadata.mnemonic
    << " (0x"
    << std::uppercase <<  std::setw(2) << std::setfill('0') << std::hex
    << instructionMatrixIndex
    << ")"
    << " / ADDR_MODE: "
    << instructionMetadata.addressModeName;
}