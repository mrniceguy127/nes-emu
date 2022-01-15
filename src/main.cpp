#include "NESIncludes.h"
#include <iostream>

int main() {
  R6502 cpu = R6502();
  cpu.reset();
  std::cout << "I do nothing yet! :D" << std::endl;
}
