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
  fetched = 0x00;
  tmp = 0x0000;

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

uint8_t R6502::getFlag(FLAGS flag) {
  return flag & P > 0 ? 1 : 0;
}

void R6502::setFlag(FLAGS flag, uint8_t value) {
  if (value) {
    P |= flag;
  } else {
    P &= ~flag;
  }
}

// -----
// Useful Methods
// -----
void R6502::fetch() {
  fetched = read(absAddr);
  return fetched;
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





// -----
// Instructions - https://www.masswerk.at/6502/6502_instruction_set.html
// -----



uint8_t R6502::ADC() {
  // A + M + C -> A, C
  // Flags changed: C Z N V

  fetch(); // fetch target data

  tmp = (uint16_t) a + (uint16_t) fetched + (uint16_t) getFlag(C);

  setFlag(C, tmp > 255);
  setFlag(Z, tmp & 0x00FF == 0); // Clear higher order bits before comparing
  setFlag(N, tmp & 0x0080);
  
  // Overflow happens when both operands have the same sign but the result is a different sign.
  // 1. XNOR the 2 operands, the MSB in the result is whether or not the signs are the same.
  // 2. check if the sign of the result differs from the sign of either operand (XOR them).
  // 3. if 1 and 2 are true, over flow occured (get the sign bit of the & of 1 and 2).
  setFlag(V, (~((uint16_t) a ^ (uint16_t) fetched) & (((uint8_t)a ^ tmp)) & 0x0080);

  a = tmp & 0x00FF;

  return 1; // Extra cycle possible.
}

uint8_t R6502::AND() {
  // A AND M -> A
  // Flags changed: Z N
  
  fetch();
  a &= fetched;

  setFlag(Z, a == 0);
  setFlag(N, a & 0x80);

  return 1;
}

uint8_t R6502::ASL() {
  return 0;
}

uint8_t R6502::BCC() {
  return 0;
}

uint8_t R6502::BCS() {
  return 0;
}

uint8_t R6502::BEQ() {
  return 0;
}

uint8_t R6502::BIT() {
  return 0;
}

uint8_t R6502::BMI() {
  return 0;
}

uint8_t R6502::BNE() {
  return 0;
}

uint8_t R6502::BPL() {
  return 0;
}

uint8_t R6502::BRK() {
  return 0;
}

uint8_t R6502::BVC() {
  return 0;
}

uint8_t R6502::BVS() {
  return 0;
}

uint8_t R6502::CLC() {
  return 0;
}

uint8_t R6502::CLD() {
  return 0;
}

uint8_t R6502::CLI() {
  return 0;
}

uint8_t R6502::CLV() {
  return 0;
}

uint8_t R6502::CMP() {
  return 0;
}

uint8_t R6502::CPX() {
  return 0;
}

uint8_t R6502::CPY() {
  return 0;
}

uint8_t R6502::DEC() {
  return 0;
}

uint8_t R6502::DEX() {
  return 0;
}

uint8_t R6502::DEY() {
  return 0;
}

uint8_t R6502::EOR() {
  return 0;
}

uint8_t R6502::INC() {
  return 0;
}

uint8_t R6502::INX() {
  return 0;
}

uint8_t R6502::INY() {
  return 0;
}

uint8_t R6502::JMP() {
  return 0;
}

uint8_t R6502::JSR() {
  return 0;
}

uint8_t R6502::LDA() {
  return 0;
}

uint8_t R6502::LDX() {
  return 0;
}

uint8_t R6502::LDY() {
  return 0;
}

uint8_t R6502::LSR() {
  return 0;
}

uint8_t R6502::NOP() {
  return 0;
}

uint8_t R6502::ORA() {
  return 0;
}

uint8_t R6502::PHA() {
  return 0;
}

uint8_t R6502::PHP() {
  return 0;
}

uint8_t R6502::PLA() {
  return 0;
}

uint8_t R6502::PLP() {
  return 0;
}

uint8_t R6502::ROL() {
  return 0;
}

uint8_t R6502::ROR() {
  return 0;
}

uint8_t R6502::RTI() {
  return 0;
}

uint8_t R6502::RTS() {
  return 0;
}

uint8_t R6502::SBC() {
  return 0;
}

uint8_t R6502::SEC() {
  return 0;
}

uint8_t R6502::SED() {
  return 0;
}

uint8_t R6502::SEI() {
  return 0;
}

uint8_t R6502::STA() {
  return 0;
}

uint8_t R6502::STX() {
  return 0;
}

uint8_t R6502::STY() {
  return 0;
}

uint8_t R6502::TAX() {
  return 0;
}

uint8_t R6502::TAY() {
  return 0;
}

uint8_t R6502::TSX() {
  return 0;
}

uint8_t R6502::TXA() {
  return 0;
}

uint8_t R6502::TXS() {
  return 0;
}

uint8_t R6502::TYA() {
  return 0;
}









uint8_t R6502::XXX() {
  return 0;
}




