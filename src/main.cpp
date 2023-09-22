#include "NESIncludes.h"
#include <iostream>

int main() {
  R6502 cpu = R6502();
  Bus bus = Bus();
  cpu.connectBus(&bus);
  cpu.init();
  std::cout << "I do nothing yet! :D" << std::endl;
}
