#include "NESIncludes.h"


// -----
// External event functions
// -----

R6502::R6502() { }
R6502::~R6502() { }

void R6502::clock() { }
void R6502::reset() {
  // Useful Variables
  absAddr = 0x0000;
  relAddr = 0x0000;

  // Registers
  a = 0x00;
  x = 0x00;
  y = 0x00;
  pc = 0x0000;
  sp = 0x00;

  // Flags
  P = 0x00;
}

uint8_t R6502::read(uint16_t addr) {
  return bus->read(addr); 
}

void R6502::write(uint16_t addr, uint8_t data) {
  bus->write(addr, data);
}

void R6502::connectBus(Bus * b) {
  bus = b;
}

// -----
// Addressing modes - http://archive.6502.org/datasheets/rockwell_r650x_r651x.pdf
// -----


// Next byte has operand. get current pc, then increment.
uint8_t R6502::IMM() {
  absAddr = pc++;
  return 0;
}  

uint8_t R6502::ABS() {
  uint16_t lo = read(pc++);
  uint16_t hi = read(pc++);
  absAddr = (hi << 8) | lo;
  return 0;
}

uint8_t R6502::ABX() {
  uint16_t lo = read(pc++);
  uint16_t hi = read(pc++);
  absAddr = (hi << 8) | lo;
  absAddr += x;
 
  // Extra cycle is needed if page bouundary crossed
  return absAddr >> 8 != hi ? 1 : 0;
}


uint8_t R6502::ABY() {
  uint16_t lo = read(pc++);
  uint16_t hi = read(pc++);
  absAddr = (hi << 8) | lo;
  absAddr += y;
 
  // Extra cycle is needed if page bouundary crossed
  return absAddr >> 8 != hi ? 1 : 0;
}


uint8_t R6502::IMP() {
  return 0;
}


uint8_t R6502::ZP0() {
  absAddr = read(pc++);
  return 0;
}


uint8_t R6502::ZPX() {
  absAddr = read(pc++) + x;
  absAddr &= 0x00FF; // no paging past the zero page may occur
  return 0;
}


uint8_t R6502::ZPY() {
  absAddr = read(pc++) + y;
  absAddr &= 0x00FF; // no paging past the zero page may occur
  return 0;
}


uint8_t R6502::REL() {
  relAddr = read(pc++);

  // if negative (MSB of lo byte == 1), set hi byte to FF since relAddr is 2 bytes, not 1 as read. This will keep the relative address negative when converted to 2 byte form.
  if (relAddr & 0x80) {
    relAddr |= 0xFF00;
  }

  return 0;
}


uint8_t R6502::IZX() {
  uint16_t baseAddr = read(pc++);
  uint16_t loAddr = (baseAddr + x) & 0x00FF;
  uint16_t hiAddr = (baseAddr + x + 1) & 0x00FF;

  uint16_t lo = read(loAddr);
  uint16_t hi = read(hiAddr);

  absAddr = (hi << 8) | lo;

  return 0;
}


uint8_t R6502::IZY() {
  uint16_t baseAddr = read(pc++);
  uint16_t lo = read(baseAddr & 0x00FF);
  uint16_t hi = read((baseAddr + 1) & 0x00FF);

  absAddr = (hi << 8) | lo;
  absAddr += y;

  return absAddr >> 8 != hi ? 1 : 0;
}


uint8_t R6502::IND() {
  // Things start to look weird here in order to simulate a bug in the CPU.
  // From hnesdev.icequake.net/6502bugs.txt:
  // "An indirect JMP (xxFF) will fail because the MSB will be fetched from
  // address xx00 instead of page xx+1."
  uint8_t pointerLo = read(pc++);
  uint8_t pointerHi = read(pc++);

  uint16_t loAddr = (((uint16_t) pointerHi) << 8) | pointerLo;
  // hiAddr is intentionally bugged. pointerLo + 1 can overflow.
  uint16_t hiAddr = (((uint16_t) pointerHi) << 8) | (pointerLo + 1);

  uint16_t lo = read(loAddr);
  uint16_t hi = read(hiAddr);

  absAddr = (hi << 8) | lo;

  return 0;
}

