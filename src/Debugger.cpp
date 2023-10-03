#include "NESIncludes.h"
#include "Debugger.h"

#include <iostream>

Debugger::Debugger(R6502* c) : cpu(c) { }
Debugger::~Debugger() { }

void Debugger::step() {
    cpu->doNextInstruction();
    showState();
}

ConsoleDebugger::ConsoleDebugger(R6502* c) : Debugger(c) { }
ConsoleDebugger::~ConsoleDebugger() { }

void ConsoleDebugger::showState() {
  R6502::State state = cpu->getState();
  std::cout
    << "<REGISTERS STATE>" << std::endl
    << "Accumulator: " << std::hex << (int)      state.accumulator << std::endl
    << "X-Index: " << std::hex << (int)          state.x << std::endl
    << "Y-Index: " << std::hex << (int)          state.y << std::endl
    << "Program Counter: " << std::hex << (int)  state.pc << std::endl
    << "Stack Pointer: " << std::hex << (int)    state.sp << std::endl
  << std::endl;
}