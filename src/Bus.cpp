#include "NESIncludes.h"

Bus::Bus() {}

Bus::~Bus() { }



void Bus::write(uint16_t addr, uint8_t data) {
  if (addr >= 0x000 && addr <= 0xFFFF) { // Bus addressing boundaries
    ram[addr] = data;
  }
}

uint8_t Bus::read(uint16_t addr) {
  if (addr >= 0x000 && addr <= 0xFFFF) { // Bus addressing boundaries
    return ram[addr];
  }
}

