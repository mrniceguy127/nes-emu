#include "NESIncludes.h"

Memory::Memory() {}

Memory::~Memory() { }



void Memory::write(uint16_t addr, uint8_t data) {
  if (addr >= 0x0000 && addr <= 0xFFFF) { // Memory addressing boundaries
    ram[addr] = data;
  }
}

uint8_t Memory::read(uint16_t addr) {
  if (addr >= 0x0000 && addr <= 0xFFFF) { // Memory addressing boundaries
    return ram[addr];
  }
  return 0x00;
}

