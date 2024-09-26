#include "../src/NESIncludes.h"
#include "../src/Debugger.h"

#include <iostream>
#include <iomanip>
#include <fstream>

uint8_t test(R6502& cpu, Memory * mem);
uint8_t testInstructionCycleAccuracy(R6502& cpu, Memory * mem, uint8_t opCode, uint8_t expectedMachineCycles);
uint8_t testSimpleProgram(R6502& cpu, Memory * mem);
uint8_t testComprehensive(R6502& cpu, Memory * mem);

int main() {
  Memory * memory = new Memory();
  R6502 cpu = R6502(memory);
  cpu.powerOn();

  //test(cpu, memory);
  testComprehensive(cpu, memory);

  return 0;
};

uint8_t assertEqual(uint8_t expected, uint8_t actual);
uint8_t assertEqual(R6502::State expected, R6502::State actual);
void printExpectedAndActual(uint8_t expected, uint8_t actual);
void printInstruction(uint8_t opCode);



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

void loadProgramFromFile(const char* filePath, Memory * mem, uint16_t pcStart) {
  std::ifstream file(filePath, std::ios::binary);

  if (!file.is_open()) {
      std::cerr << "Failed to open file: " << filePath << std::endl;
      return;
  }

  const size_t buffer_size = 1024;
  unsigned int page = 0;
  std::vector<char> buffer(buffer_size);

  // Read and process bytes using a buffer
  while (true) {
      file.read(buffer.data(), buffer_size);
      std::streamsize bytesRead = file.gcount(); // Number of bytes read in the last read operation

      if (bytesRead > 0) {
          // Process the bytes in the buffer
          for (std::streamsize i = 0; i < bytesRead; ++i) {
              // Process buffer[i] as needed
              unsigned int address = (page * buffer_size) + i;
              mem->write(pcStart + address, buffer[i]);
              //std::cout << std::hex << (int) address << " " << std::endl;
          }
      } else {
          // End of file reached
          break;
      }
    
    page++;
  }

  // Check for errors during the read operation
  if (file.fail() && !file.eof()) {
      std::cerr << "Error reading file: " << filePath << std::endl;
      file.close();
      return;
  }

  // Close the file
  file.close();
}

uint8_t testComprehensive(R6502& cpu, Memory * mem) {
  cpu.powerOn();
  //https://github.com/Klaus2m5/6502_65C02_functional_tests/blob/master/bin_files/6502_functional_test.lst
  // Config???
  cpu.memory->write(0x0001, 0x00); // Disable rom vectors
  cpu.memory->write(0x0001, 0x00); // Disable load data direct
  cpu.memory->write(0x0003, 0x00); // Allow I Flag
  cpu.memory->write(0x000A, 0x0A); // Zero page start (system mem)
  cpu.memory->write(0x0200, 0x00); // Data segment start (low byte)
  cpu.memory->write(0x0201, 0x02); // Data segment start (high byte)
  cpu.memory->write(0x0400, 0x00); // Code segment start (low byte)
  cpu.memory->write(0x0401, 0x04); // Code segment start (high byte)

  //cpu.setFlags(0x20, 0);


  cpu.pc = 0x0400;
  loadProgramFromFile("test/test-programs/6502_functional_test.bin", mem, 0);
  ConsoleDebugger debugger = ConsoleDebugger(&cpu);
  //debugger.showState();

  int instructionsPassed = 0;
  uint8_t hitIllegal = 0x00;
  uint8_t hitJMP = 0x00;
  uint8_t trapHit = 0x00;
  while (true) {
    if (hitIllegal) {
      std::cout << "Illegal instruction hit!" << std::endl;
      //debugger.showState();
      break;
    }
    else if (hitJMP == 0x02) {
      //debugger.step();
      hitJMP--;
    }

    /*const uint16_t traps[] = {
      05e6
    };*/

    // detect traps
    if (
      trapHit != 0 //||
      //cpu.pc == 0x0674 || // Branch should be taken
      //cpu.pc == 0x37C9 ||
      //cpu.pc == 0x3778
      //cpu.pc == 0x0D96
      //cpu.pc == 0x0E68
      //cpu.pc == 0x0E5A
      //cpu.pc == 0x0F65
      //cpu.pc == 0x17AD
      //cpu.pc == 0x16FC
    ) {
      std::cout << "Trap hit!" << std::endl;
      debugger.showState();
      //debugger.showState();
      debugger.step();
      std::cout << "mem: " << std::hex << (int) cpu.memory->read(0x0015) << std::endl;
      std::cout << "mem: " << std::hex << (int) cpu.memory->read(0x0016) << std::endl;
      std::cout << "mem: " << std::hex << (int) cpu.memory->read(0x0017) << std::endl;
      std::cout << "mem: " << std::hex << (int) cpu.memory->read(0x0018) << std::endl;
      trapHit = 1;
    }
    cpu.doNextInstruction();

    if (cpu.pc == 0x3469) {
      std::cout << "Success on comprehensive tests!" << std::endl;
      break;
    }

    if(R6502::getInstructionMatrix()[cpu.getCurrentOpCode()].addressMode == R6502::ILLMODE) {
      hitIllegal = 0x01;
    }

    if(R6502::getInstructionMatrix()[cpu.getCurrentOpCode()].operation == R6502::JMP) {
      hitJMP++;
    } else if (hitJMP > 0x00) {
    }

    debugger.showState();
    //debugger.step();
    instructionsPassed++;
  }

  std::cout << "END COMPREHENSIVE" << std::endl;

  //debugger.showState();

  return 0x00;
}