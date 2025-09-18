#include "NESIncludes.h"
#include <iostream>

Memory::Memory() {
  AddressMappingFunction* defaultMappingFunction = new AddressMappingFunction(ram);
  for (uint32_t i = 0; i <= 0xFFFF; i++) {
    addressMap[i] = defaultMappingFunction;
  }
}

Memory::~Memory() { }



void Memory::write(uint16_t addr, uint8_t data) {
  if (addr >= 0x0000 && addr <= 0xFFFF) { // Memory addressing boundaries
    addressMap[addr]->write(addr, data);
  }
}

uint8_t Memory::read(uint16_t addr) {
  if (addr >= 0x0000 && addr <= 0xFFFF) { // Memory addressing boundaries
    return addressMap[addr]->read(addr);
  }
  return 0x00;
}

void Memory::mapAddress(uint16_t addr, AddressMappingFunction* addressMappingFunction) {
  addressMap[addr] = addressMappingFunction;
}

void Memory::mapAddressRange(uint16_t startAddr, uint16_t endAddr, AddressMappingFunction* addressMappingFunction) {
  for (uint16_t addr = startAddr; addr <= endAddr; addr++) {
    mapAddress(addr, addressMappingFunction);
  }
}


AddressMappingFunction::AddressMappingFunction(std::array<uint8_t, 0x10000>& memory) : memory(memory) {}
uint8_t AddressMappingFunction::read(uint16_t addr) {
  return memory[addr];
}
void AddressMappingFunction::write(uint16_t addr, uint8_t data) {     
  memory[addr] = data;
}
