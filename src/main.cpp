#include "NESIncludes.h"
#include <iostream>

uint8_t test(R6502& cpu, Memory& memory);

int main() {
  Memory memory = Memory();
  R6502 cpu = R6502(memory);
  cpu.init();
  test(cpu, memory);
}

uint8_t test(R6502& cpu, Memory& memory) {
  // Load up test program. Returns true if success.
  std::cout << "I do nothing yet! :D" << std::endl;
  return 0x01;
}