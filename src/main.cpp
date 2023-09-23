#include "NESIncludes.h"
#include <iostream>

int main() {
  Memory memory = Memory();
  R6502 cpu = R6502(memory);
  cpu.init();
  std::cout << "I do nothing yet! :D" << std::endl;
}
