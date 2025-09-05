#include "NESIncludes.h"
#include <iostream>

Memory::Memory() {
  for (uint32_t i = 0; i <= 0xFFFF; i++) {
    addressMap[i] = reinterpret_cast<uint64_t>(ram.data()) + i;
  }
}

Memory::~Memory() { }



void Memory::write(uint16_t addr, uint8_t data) {
  if (addr >= 0x0000 && addr <= 0xFFFF) { // Memory addressing boundaries
    *reinterpret_cast<uint8_t*>(addressMap[addr]) = data;
  }
}

uint8_t Memory::read(uint16_t addr) {
  if (addr >= 0x0000 && addr <= 0xFFFF) { // Memory addressing boundaries
    return *reinterpret_cast<uint8_t*>(addressMap[addr]);
  }
  return 0x00;
}

void Memory::mapAddress(uint16_t addr, uint64_t pointer) {
  addressMap[addr] = pointer;
}

void Memory::mapAddressRange(uint16_t startAddr, uint16_t endAddr, uint64_t pointer) {
  for (uint16_t addr = startAddr; addr <= endAddr; addr++) {
    addressMap[addr] = pointer + (addr - startAddr);
  }
}

