#include "NESIncludes.h"


// -----
// External event functions
// -----

R6502::R6502() {
  // Generated using script located at util/generate-matrix.sh
  instructionMatrix = 
  {
	  /* 0                                      1                                      2                                      3                                      4                                      5                                      6                                      7                                      8                                      9                                      A                                      B                                      C                                      D                                      E                                      F                                      */
  /* 0 */    { "BRK", &R6502:IMP, &R6502:BRK, 7}, { "ORA", &R6502:IZX, &R6502:ORA, 6}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "ORA", &R6502:ZP0, &R6502:ORA, 3}, { "ASL", &R6502:ZP0, &R6502:ASL, 5}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "PHP", &R6502:IMP, &R6502:PHP, 3}, { "ORA", &R6502:IMM, &R6502:ORA, 2}, { "ASL", &R6502:IMP, &R6502:ASL, 2}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "ORA", &R6502:ABS, &R6502:ORA, 4}, { "ASL", &R6502:ABS, &R6502:ASL, 6}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, 
  /* 1 */    { "BPL", &R6502:REL, &R6502:BPL, 2}, { "ORA", &R6502:IZY, &R6502:ORA, 5}, { "XXX", &R6502:XXX, &R6502:XXX, X}, { "XXX", &R6502:XXX, &R6502:XXX, X}, { "XXX", &R6502:XXX, &R6502:XXX, X}, { "ORA", &R6502:ZPX, &R6502:ORA, 4}, { "ASL", &R6502:ZPX, &R6502:ASL, 6}, { "XXX", &R6502:XXX, &R6502:XXX, X}, { "CLC", &R6502:IMP, &R6502:CLC, 2}, { "ORA", &R6502:ABY, &R6502:ORA, 4}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "ORA", &R6502:ABX, &R6502:ORA, 4}, { "ASL", &R6502:ABX, &R6502:ASL, 7}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, 
  /* 2 */    { "JSR", &R6502:XXX, &R6502:JSR, 6}, { "AND", &R6502:IZX, &R6502:AND, 6}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "BIT", &R6502:ZP0, &R6502:BIT, 3}, { "AND", &R6502:ZP0, &R6502:AND, 3}, { "ROL", &R6502:ZP0, &R6502:ROL, 5}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "PLP", &R6502:IMP, &R6502:PLP, 4}, { "AND", &R6502:IMM, &R6502:AND, 2}, { "ROL", &R6502:IMP, &R6502:ROL, 2}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "BIT", &R6502:ABS, &R6502:BIT, 4}, { "AND", &R6502:ABS, &R6502:AND, 4}, { "ROL", &R6502:ABS, &R6502:ROL, 6}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, 
  /* 3 */    { "BMI", &R6502:REL, &R6502:BMI, 2}, { "AND", &R6502:IZY, &R6502:AND, 5}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "AND", &R6502:ZPX, &R6502:AND, 4}, { "ROL", &R6502:ZPX, &R6502:ROL, 6}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "SEC", &R6502:IMP, &R6502:SEC, 2}, { "AND", &R6502:ABY, &R6502:AND, 4}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "AND", &R6502:ABX, &R6502:AND, 4}, { "ROL", &R6502:ABX, &R6502:ROL, 7}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, 
  /* 4 */    { "RTI", &R6502:IMP, &R6502:RTI, 6}, { "EOR", &R6502:IZX, &R6502:EOR, 6}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "EOR", &R6502:ZP0, &R6502:EOR, 3}, { "LSR", &R6502:ZP0, &R6502:LSR, 5}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "PHA", &R6502:IMP, &R6502:PHA, 3}, { "EOR", &R6502:IMM, &R6502:EOR, 2}, { "LSR", &R6502:IMP, &R6502:LSR, 2}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "JMP", &R6502:ABS, &R6502:JMP, 3}, { "EOR", &R6502:ABS, &R6502:EOR, 4}, { "LSR", &R6502:ABS, &R6502:LSR, 6}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, 
  /* 5 */    { "BVC", &R6502:REL, &R6502:BVC, 2}, { "EOR", &R6502:IZY, &R6502:EOR, 5}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "EOR", &R6502:ZPX, &R6502:EOR, 4}, { "LSR", &R6502:ZPX, &R6502:LSR, 6}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "CLI", &R6502:IMP, &R6502:CLI, 2}, { "EOR", &R6502:ABY, &R6502:EOR, 4}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "EOR", &R6502:ABX, &R6502:EOR, 4}, { "LSR", &R6502:ABX, &R6502:LSR, 7}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, 
  /* 6 */    { "RTS", &R6502:IMP, &R6502:RTS, 6}, { "ADC", &R6502:IZX, &R6502:ADC, 6}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "ADC", &R6502:ZP0, &R6502:ADC, 3}, { "ROR", &R6502:ZP0, &R6502:ROR, 5}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "PLA", &R6502:IMP, &R6502:PLA, 4}, { "ADC", &R6502:IMM, &R6502:ADC, 2}, { "ROR", &R6502:IMP, &R6502:ROR, 2}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "JMP", &R6502:XXX, &R6502:JMP, 5}, { "ADC", &R6502:ABS, &R6502:ADC, 4}, { "ROR", &R6502:ABS, &R6502:ROR, 6}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, 
  /* 7 */    { "BVS", &R6502:REL, &R6502:BVS, 2}, { "ADC", &R6502:IZY, &R6502:ADC, 5}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "ADC", &R6502:ZPX, &R6502:ADC, 4}, { "ROR", &R6502:ZPX, &R6502:ROR, 6}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "SEI", &R6502:IMP, &R6502:SEI, 2}, { "ADC", &R6502:ABY, &R6502:ADC, 4}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "ADC", &R6502:ABX, &R6502:ADC, 4}, { "ROR", &R6502:ABX, &R6502:ROR, 7}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, 
  /* 8 */    { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "STA", &R6502:IZX, &R6502:STA, 6}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "STY", &R6502:ZP0, &R6502:STY, 3}, { "STA", &R6502:ZP0, &R6502:STA, 3}, { "STX", &R6502:ZP0, &R6502:STX, 3}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "DEY", &R6502:IMP, &R6502:DEY, 2}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "TXA", &R6502:IMP, &R6502:TXA, 2}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "STY", &R6502:ABS, &R6502:STY, 4}, { "STA", &R6502:ABS, &R6502:STA, 4}, { "STX", &R6502:ABS, &R6502:STX, 4}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, 
  /* 9 */    { "BCC", &R6502:REL, &R6502:BCC, 2}, { "STA", &R6502:IZY, &R6502:STA, 6}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "STY", &R6502:ZPX, &R6502:STY, 4}, { "STA", &R6502:ZPX, &R6502:STA, 4}, { "STX", &R6502:ZPY, &R6502:STX, 4}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "TYA", &R6502:IMP, &R6502:TYA, 2}, { "STA", &R6502:ABY, &R6502:STA, 5}, { "TXS", &R6502:IMP, &R6502:TXS, 2}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "STA", &R6502:ABX, &R6502:STA, 5}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, 
  /* A */    { "LDY", &R6502:IMM, &R6502:LDY, 2}, { "LDA", &R6502:IZX, &R6502:LDA, 6}, { "LDX", &R6502:IMM, &R6502:LDX, 2}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "LDY", &R6502:ZP0, &R6502:LDY, 3}, { "LDA", &R6502:ZP0, &R6502:LDA, 3}, { "LDX", &R6502:ZP0, &R6502:LDX, 3}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "TAY", &R6502:IMP, &R6502:TAY, 2}, { "LDA", &R6502:IMM, &R6502:LDA, 2}, { "TAX", &R6502:IMP, &R6502:TAX, 2}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "LDY", &R6502:ABS, &R6502:LDY, 4}, { "LDA", &R6502:ABS, &R6502:LDA, 4}, { "LDX", &R6502:ABS, &R6502:LDX, 4}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, 
  /* B */    { "BCS", &R6502:REL, &R6502:BCS, 2}, { "LDA", &R6502:IZY, &R6502:LDA, 5}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "LDY", &R6502:ZPX, &R6502:LDY, 4}, { "LDA", &R6502:ZPX, &R6502:LDA, 4}, { "LDX", &R6502:ZPY, &R6502:LDX, 4}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "CLV", &R6502:IMP, &R6502:CLV, 2}, { "LDA", &R6502:ABY, &R6502:LDA, 4}, { "TSX", &R6502:IMP, &R6502:TSX, 2}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "LDY", &R6502:ABX, &R6502:LDY, 4}, { "LDA", &R6502:ABX, &R6502:LDA, 4}, { "LDX", &R6502:ABY, &R6502:LDX, 4}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, 
  /* C */    { "CPY", &R6502:IMM, &R6502:CPY, 2}, { "CMP", &R6502:IZX, &R6502:CMP, 6}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "CPY", &R6502:ZP0, &R6502:CPY, 3}, { "CMP", &R6502:ZP0, &R6502:CMP, 3}, { "DEC", &R6502:ZP0, &R6502:DEC, 5}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "INY", &R6502:IMP, &R6502:INY, 2}, { "CMP", &R6502:IMM, &R6502:CMP, 2}, { "DEX", &R6502:IMP, &R6502:DEX, 2}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "CPY", &R6502:ABS, &R6502:CPY, 4}, { "CMP", &R6502:ABS, &R6502:CMP, 4}, { "DEC", &R6502:ABS, &R6502:DEC, 6}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, 
  /* D */    { "BNE", &R6502:REL, &R6502:BNE, 2}, { "CMP", &R6502:IZY, &R6502:CMP, 5}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "CMP", &R6502:ZPX, &R6502:CMP, 4}, { "DEC", &R6502:ZPX, &R6502:DEC, 6}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "CLD", &R6502:IMP, &R6502:CLD, 2}, { "CMP", &R6502:ABY, &R6502:CMP, 4}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "CMP", &R6502:ABX, &R6502:CMP, 4}, { "DEC", &R6502:ABX, &R6502:DEC, 7}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, 
  /* E */    { "CPX", &R6502:IMM, &R6502:CPX, 2}, { "SBC", &R6502:IZX, &R6502:SBC, 6}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "CPX", &R6502:ZP0, &R6502:CPX, 3}, { "SBC", &R6502:ZP0, &R6502:SBC, 3}, { "INC", &R6502:ZP0, &R6502:INC, 5}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "INX", &R6502:IMP, &R6502:INX, 2}, { "SBC", &R6502:IMM, &R6502:SBC, 2}, { "NOP", &R6502:IMP, &R6502:NOP, 2}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "CPX", &R6502:ABS, &R6502:CPX, 4}, { "SBC", &R6502:ABS, &R6502:SBC, 4}, { "INC", &R6502:ABS, &R6502:INC, 6}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, 
  /* F */    { "BEQ", &R6502:REL, &R6502:BEQ, 2}, { "SBC", &R6502:IZY, &R6502:SBC, 5}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "SBC", &R6502:ZPX, &R6502:SBC, 4}, { "INC", &R6502:ZPX, &R6502:INC, 6}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "SED", &R6502:IMP, &R6502:SED, 2}, { "SBC", &R6502:ABY, &R6502:SBC, 4}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "XXX", &R6502:XXX, &R6502:XXX, 0}, { "SBC", &R6502:ABX, &R6502:SBC, 4}, { "INC", &R6502:ABX, &R6502:INC, 7}, { "XXX", &R6502:XXX, &R6502:XXX, 0} 
  }
}

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
 
  // Extra cycle is needed if page boundary crossed
  return absAddr >> 8 != hi ? 1 : 0;
}


uint8_t R6502::ABY() {
  uint16_t lo = read(pc++);
  uint16_t hi = read(pc++);
  absAddr = (hi << 8) | lo;
  absAddr += y;
 
  // Extra cycle is needed if page boundary crossed
  return absAddr >> 8 != hi ? 1 : 0;
}


uint8_t R6502::IMP() {
  fetched = a;
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
  // C <- [76543210] <- 0
  // Flags changed: C Z N
  
  fetch();
  
  tmp = (uint16_t) fetched << 1;

  setFlag(C, (tmp & 0xFF00) > 0);
  setFlag(Z, tmp == 0);
  setFlag(N, tmp & 0x0800);

  if (instructionMatrix[opcode].addressMode == &R6502::IMP) { // Implied is same as accumulator addressing mode technically.
    a = tmp & 0x00FF;
  } else {
    write(absAddr, tmp & 0x00FF);
  }

  return 0;
}

uint8_t R6502::BCC() {
  // branch on C = 0
  // Flags changed: 

  fetch();
  
  if (getFlag(C) == 0) {
    absAddr = fetched;
    if (fetched & 0xFF00 != absAddr & 0xFF00) {
      cycles++;
    }
    cycles++;
  }

  return 0;
}

uint8_t R6502::BCS() {
  // branch on C = 1
  // Flags changed: 

  fetch();
  
  if (getFlag(C) == 1) {
    absAddr = fetched;
    if (fetched & 0xFF00 != absAddr & 0xFF00) {
      cycles++;
    }
    cycles++;
  }

  return 0;
}

uint8_t R6502::BEQ() {
  // branch on Z = 1
  // Flags changed: 

  fetch();
  
  if (getFlag(Z) == 1) {
    absAddr = fetched;
    if (fetched & 0xFF00 != absAddr & 0xFF00) {
      cycles++;
    }
    cycles++;
  }

  return 0;
}

uint8_t R6502::BIT() {
  // A AND M, M7 -> N, M6 -> V
  // Flags changed: Z N V
  
  fetch();
  
  setFlag(Z, a & fetched == 0x00);
  setFlag(N, fetched & (1 << 7));
  setFlag(V, fetched & (1 << 6));

  return 0;
}

uint8_t R6502::BMI() {
  // branch on N = 1
  // Flags changed: 

  fetch();
  
  if (getFlag(N) == 1) {
    absAddr = fetched;
    if (fetched & 0xFF00 != absAddr & 0xFF00) {
      cycles++;
    }
    cycles++;
  }

  return 0;
}

uint8_t R6502::BNE() {
  // branch on Z = 0
  // Flags changed: 

  fetch();
  
  if (getFlag(Z) == 0) {
    absAddr = fetched;
    if (fetched & 0xFF00 != absAddr & 0xFF00) {
      cycles++;
    }
    cycles++;
  }

  return 0;
}

uint8_t R6502::BPL() {
  // branch on N = 0
  // Flags changed: 

  fetch();
  
  if (getFlag(N) == 0) {
    absAddr = fetched;
    if (fetched & 0xFF00 != absAddr & 0xFF00) {
      cycles++;
    }
    cycles++;
  }

  return 0;
}

uint8_t R6502::BRK() { // Here we will be pushing to the stack. Back to the wiki and then will come back after break :sweat_smile:
  return 0;
}

uint8_t R6502::BVC() {
  // branch on V = 0
  // Flags changed: 

  fetch();
  
  if (getFlag(V) == 0) {
    absAddr = fetched;
    if (fetched & 0xFF00 != absAddr & 0xFF00) {
      cycles++;
    }
    cycles++;
  }

  return 0;
}

uint8_t R6502::BVS() {
  // branch on V = 1
  // Flags changed: 

  fetch();
  
  if (getFlag(V) == 1) {
    absAddr = fetched;
    if (fetched & 0xFF00 != absAddr & 0xFF00) {
      cycles++;
    }
    cycles++;
  }

  return 0;
}

uint8_t R6502::CLC() {
  // 0 -> C
  // Flags changed: C
  setFlag(C, 0);
  return 0;
}

uint8_t R6502::CLD() {
  // 0 -> D
  // Flags changed: D
  setFlag(D, 0);
  return 0;
}

uint8_t R6502::CLI() {
  // 0 -> I
  // Flags changed: I
  setFlag(I, 0);
  return 0;
}

uint8_t R6502::CLV() {
  // 0 -> V
  // Flags changed: V
  setFlag(V, 0);
  return 0;
}

uint8_t R6502::CMP() {
  // A - M
  // Flags changed: N Z C
  fetch();

  tmp = ((uint16_t) a - (uint16_t) fetched) & 0x00FF;

  setFlag(N, tmp & 0x0080);
  setFlag(Z, tmp == 0x0000);
  setFlag(C, a >= fetched);
  return 1;
}

uint8_t R6502::CPX() {
  // X - M
  // Flags changed: N Z C
  fetch();

  tmp = ((uint16_t) x - (uint16_t) fetched) & 0x00FF;

  setFlag(N, tmp & 0x0080);
  setFlag(Z, tmp == 0x0000);
  setFlag(C, x >= fetched);
  return 0;
}

uint8_t R6502::CPY() {
  // Y - M
  // Flags changed: N Z C
  fetch();

  tmp = ((uint16_t) y - (uint16_t) fetched) & 0x00FF;

  setFlag(N, tmp & 0x0080);
  setFlag(Z, tmp == 0x0000);
  setFlag(C, y >= fetched);
  return 0;
}

uint8_t R6502::DEC() {
  // M - 1 -> M
  // Flags changed: Z N
  
  fetch();
  tmp = ((uint16_t) fetched - 1) & 0x00FF;

  write(absAddr, tmp);
  
  setFlag(Z, tmp == 0x0000);
  setFlag(N, tmp & 0x0080);

  return 0;
}

uint8_t R6502::DEX() {
  // X - 1 -> X
  // Flags changed: Z N

  x = x - 1;
  
  setFlag(Z, x == 0x0000);
  setFlag(N, x & 0x0080);

  return 0;
}

uint8_t R6502::DEY() {
  // Y - 1 -> Y
  // Flags changed: Z N

  y = y - 1;
  
  setFlag(Z, y == 0x0000);
  setFlag(N, y & 0x0080);

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




