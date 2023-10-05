#include "NESIncludes.h"
#include "Debugger.h"

void debug(R6502 * cpu);

int main() {
  Memory * memory = new Memory();
  R6502 cpu = R6502(memory);
  cpu.powerOn();
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
