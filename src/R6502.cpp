#include "NESIncludes.h"

// -----
// External event functions
// -----

R6502::R6502() {
  // Generated using script located at util/generate-matrix.sh
  instructionMatrix =
  {
	  /* 0                                    1                                    2                                    3                                    4                                    5                                    6                                    7                                    8                                    9                                    A                                    B                                    C                                    D                                    E                                    F                                    */
  /* 0 */    { "BRK", &R6502::IMP, &R6502::BRK, 7}, { "ORA", &R6502::IZX, &R6502::ORA, 6}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "ORA", &R6502::ZP0, &R6502::ORA, 3}, { "ASL", &R6502::ZP0, &R6502::ASL, 5}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "PHP", &R6502::IMP, &R6502::PHP, 3}, { "ORA", &R6502::IMM, &R6502::ORA, 2}, { "ASL", &R6502::IMP, &R6502::ASL, 2}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "ORA", &R6502::ABS, &R6502::ORA, 4}, { "ASL", &R6502::ABS, &R6502::ASL, 6}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, 
  /* 1 */    { "BPL", &R6502::REL, &R6502::BPL, 2}, { "ORA", &R6502::IZY, &R6502::ORA, 5}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "ORA", &R6502::ZPX, &R6502::ORA, 4}, { "ASL", &R6502::ZPX, &R6502::ASL, 6}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "CLC", &R6502::IMP, &R6502::CLC, 2}, { "ORA", &R6502::ABY, &R6502::ORA, 4}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "ORA", &R6502::ABX, &R6502::ORA, 4}, { "ASL", &R6502::ABX, &R6502::ASL, 7}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, 
  /* 2 */    { "JSR", &R6502::XXX, &R6502::JSR, 6}, { "AND", &R6502::IZX, &R6502::AND, 6}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "BIT", &R6502::ZP0, &R6502::BIT, 3}, { "AND", &R6502::ZP0, &R6502::AND, 3}, { "ROL", &R6502::ZP0, &R6502::ROL, 5}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "PLP", &R6502::IMP, &R6502::PLP, 4}, { "AND", &R6502::IMM, &R6502::AND, 2}, { "ROL", &R6502::IMP, &R6502::ROL, 2}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "BIT", &R6502::ABS, &R6502::BIT, 4}, { "AND", &R6502::ABS, &R6502::AND, 4}, { "ROL", &R6502::ABS, &R6502::ROL, 6}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, 
  /* 3 */    { "BMI", &R6502::REL, &R6502::BMI, 2}, { "AND", &R6502::IZY, &R6502::AND, 5}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "AND", &R6502::ZPX, &R6502::AND, 4}, { "ROL", &R6502::ZPX, &R6502::ROL, 6}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "SEC", &R6502::IMP, &R6502::SEC, 2}, { "AND", &R6502::ABY, &R6502::AND, 4}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "AND", &R6502::ABX, &R6502::AND, 4}, { "ROL", &R6502::ABX, &R6502::ROL, 7}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, 
  /* 4 */    { "RTI", &R6502::IMP, &R6502::RTI, 6}, { "EOR", &R6502::IZX, &R6502::EOR, 6}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "EOR", &R6502::ZP0, &R6502::EOR, 3}, { "LSR", &R6502::ZP0, &R6502::LSR, 5}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "PHA", &R6502::IMP, &R6502::PHA, 3}, { "EOR", &R6502::IMM, &R6502::EOR, 2}, { "LSR", &R6502::IMP, &R6502::LSR, 2}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "JMP", &R6502::ABS, &R6502::JMP, 3}, { "EOR", &R6502::ABS, &R6502::EOR, 4}, { "LSR", &R6502::ABS, &R6502::LSR, 6}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, 
  /* 5 */    { "BVC", &R6502::REL, &R6502::BVC, 2}, { "EOR", &R6502::IZY, &R6502::EOR, 5}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "EOR", &R6502::ZPX, &R6502::EOR, 4}, { "LSR", &R6502::ZPX, &R6502::LSR, 6}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "CLI", &R6502::IMP, &R6502::CLI, 2}, { "EOR", &R6502::ABY, &R6502::EOR, 4}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "EOR", &R6502::ABX, &R6502::EOR, 4}, { "LSR", &R6502::ABX, &R6502::LSR, 7}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, 
  /* 6 */    { "RTS", &R6502::IMP, &R6502::RTS, 6}, { "ADC", &R6502::IZX, &R6502::ADC, 6}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "ADC", &R6502::ZP0, &R6502::ADC, 3}, { "ROR", &R6502::ZP0, &R6502::ROR, 5}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "PLA", &R6502::IMP, &R6502::PLA, 4}, { "ADC", &R6502::IMM, &R6502::ADC, 2}, { "ROR", &R6502::IMP, &R6502::ROR, 2}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "JMP", &R6502::XXX, &R6502::JMP, 5}, { "ADC", &R6502::ABS, &R6502::ADC, 4}, { "ROR", &R6502::ABS, &R6502::ROR, 6}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, 
  /* 7 */    { "BVS", &R6502::REL, &R6502::BVS, 2}, { "ADC", &R6502::IZY, &R6502::ADC, 5}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "ADC", &R6502::ZPX, &R6502::ADC, 4}, { "ROR", &R6502::ZPX, &R6502::ROR, 6}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "SEI", &R6502::IMP, &R6502::SEI, 2}, { "ADC", &R6502::ABY, &R6502::ADC, 4}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "ADC", &R6502::ABX, &R6502::ADC, 4}, { "ROR", &R6502::ABX, &R6502::ROR, 7}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, 
  /* 8 */    { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "STA", &R6502::IZX, &R6502::STA, 6}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "STY", &R6502::ZP0, &R6502::STY, 3}, { "STA", &R6502::ZP0, &R6502::STA, 3}, { "STX", &R6502::ZP0, &R6502::STX, 3}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "DEY", &R6502::IMP, &R6502::DEY, 2}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "TXA", &R6502::IMP, &R6502::TXA, 2}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "STY", &R6502::ABS, &R6502::STY, 4}, { "STA", &R6502::ABS, &R6502::STA, 4}, { "STX", &R6502::ABS, &R6502::STX, 4}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, 
  /* 9 */    { "BCC", &R6502::REL, &R6502::BCC, 2}, { "STA", &R6502::IZY, &R6502::STA, 6}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "STY", &R6502::ZPX, &R6502::STY, 4}, { "STA", &R6502::ZPX, &R6502::STA, 4}, { "STX", &R6502::ZPY, &R6502::STX, 4}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "TYA", &R6502::IMP, &R6502::TYA, 2}, { "STA", &R6502::ABY, &R6502::STA, 5}, { "TXS", &R6502::IMP, &R6502::TXS, 2}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "STA", &R6502::ABX, &R6502::STA, 5}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, 
  /* A */    { "LDY", &R6502::IMM, &R6502::LDY, 2}, { "LDA", &R6502::IZX, &R6502::LDA, 6}, { "LDX", &R6502::IMM, &R6502::LDX, 2}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "LDY", &R6502::ZP0, &R6502::LDY, 3}, { "LDA", &R6502::ZP0, &R6502::LDA, 3}, { "LDX", &R6502::ZP0, &R6502::LDX, 3}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "TAY", &R6502::IMP, &R6502::TAY, 2}, { "LDA", &R6502::IMM, &R6502::LDA, 2}, { "TAX", &R6502::IMP, &R6502::TAX, 2}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "LDY", &R6502::ABS, &R6502::LDY, 4}, { "LDA", &R6502::ABS, &R6502::LDA, 4}, { "LDX", &R6502::ABS, &R6502::LDX, 4}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, 
  /* B */    { "BCS", &R6502::REL, &R6502::BCS, 2}, { "LDA", &R6502::IZY, &R6502::LDA, 5}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "LDY", &R6502::ZPX, &R6502::LDY, 4}, { "LDA", &R6502::ZPX, &R6502::LDA, 4}, { "LDX", &R6502::ZPY, &R6502::LDX, 4}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "CLV", &R6502::IMP, &R6502::CLV, 2}, { "LDA", &R6502::ABY, &R6502::LDA, 4}, { "TSX", &R6502::IMP, &R6502::TSX, 2}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "LDY", &R6502::ABX, &R6502::LDY, 4}, { "LDA", &R6502::ABX, &R6502::LDA, 4}, { "LDX", &R6502::ABY, &R6502::LDX, 4}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, 
  /* C */    { "CPY", &R6502::IMM, &R6502::CPY, 2}, { "CMP", &R6502::IZX, &R6502::CMP, 6}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "CPY", &R6502::ZP0, &R6502::CPY, 3}, { "CMP", &R6502::ZP0, &R6502::CMP, 3}, { "DEC", &R6502::ZP0, &R6502::DEC, 5}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "INY", &R6502::IMP, &R6502::INY, 2}, { "CMP", &R6502::IMM, &R6502::CMP, 2}, { "DEX", &R6502::IMP, &R6502::DEX, 2}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "CPY", &R6502::ABS, &R6502::CPY, 4}, { "CMP", &R6502::ABS, &R6502::CMP, 4}, { "DEC", &R6502::ABS, &R6502::DEC, 6}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, 
  /* D */    { "BNE", &R6502::REL, &R6502::BNE, 2}, { "CMP", &R6502::IZY, &R6502::CMP, 5}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "CMP", &R6502::ZPX, &R6502::CMP, 4}, { "DEC", &R6502::ZPX, &R6502::DEC, 6}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "CLD", &R6502::IMP, &R6502::CLD, 2}, { "CMP", &R6502::ABY, &R6502::CMP, 4}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "CMP", &R6502::ABX, &R6502::CMP, 4}, { "DEC", &R6502::ABX, &R6502::DEC, 7}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, 
  /* E */    { "CPX", &R6502::IMM, &R6502::CPX, 2}, { "SBC", &R6502::IZX, &R6502::SBC, 6}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "CPX", &R6502::ZP0, &R6502::CPX, 3}, { "SBC", &R6502::ZP0, &R6502::SBC, 3}, { "INC", &R6502::ZP0, &R6502::INC, 5}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "INX", &R6502::IMP, &R6502::INX, 2}, { "SBC", &R6502::IMM, &R6502::SBC, 2}, { "NOP", &R6502::IMP, &R6502::NOP, 2}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "CPX", &R6502::ABS, &R6502::CPX, 4}, { "SBC", &R6502::ABS, &R6502::SBC, 4}, { "INC", &R6502::ABS, &R6502::INC, 6}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, 
  /* F */    { "BEQ", &R6502::REL, &R6502::BEQ, 2}, { "SBC", &R6502::IZY, &R6502::SBC, 5}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "SBC", &R6502::ZPX, &R6502::SBC, 4}, { "INC", &R6502::ZPX, &R6502::INC, 6}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "SED", &R6502::IMP, &R6502::SED, 2}, { "SBC", &R6502::ABY, &R6502::SBC, 4}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "XXX", &R6502::XXX, &R6502::XXX, 0}, { "SBC", &R6502::ABX, &R6502::SBC, 4}, { "INC", &R6502::ABX, &R6502::INC, 7}, { "XXX", &R6502::XXX, &R6502::XXX, 0} 
  };
}

R6502::~R6502() { }



static uint16_t totalCyclesPassed = 0; // Temp variablee for testing doCycle


void R6502::doCycle() {
  // https://wiki.nesdev.org/w/index.php?title=Cycle_counting
  cycles++; // This won't be needed because of this function. Remove later, but keep for now so I can actually visualize what I'm changing.
  totalCyclesPassed++;
}

uint16_t R6502::incPC() {
  return pc++;
}


void R6502::clock() { }
void R6502::reset() {
  // Useful Variables
  absAddr = 0x0000;
  relAddr = 0x0000;
  fetched = 0x00;
  tmp = 0x0000;

  a = 0x00;
  x = 0x00;
  y = 0x00;

  // SP is initialized to 0. // https://www.pagetable.com/?p=410
  sp = 0x00; 

  // https://wiki.nesdev.org/w/index.php?title=CPU_power_up_state
  // "After Reset"
  // A, X, Y were not affected
  // S was decremented by 3 (but nothing was written to the stack)
  // SEE ALSO https://www.pagetable.com/?p=410
  sp -= 3;
  // The I (IRQ disable) flag was set to true (status ORed with $04)
  P = 0x00 | I;
  // And finally, the internal memory was unchanged

  // "...loads the program counter from the memory vector locations FFFC and FFFD..."
  // (Page 2 under RESET (RES)) http://archive.6502.org/datasheets/rockwell_r650x_r651x.pdf
  pc = ((uint16_t)read(0xFFFC) << 8) | ((uint16_t)read(0xFFFD));
}

uint8_t R6502::read(uint16_t addr) {
  doCycle();
  return bus->read(addr); 
}

void R6502::write(uint16_t addr, uint8_t data) {
  doCycle();
  bus->write(addr, data);
}

uint8_t R6502::pullStack() {
  uint8_t tmp = ++sp;
  doCycle();
  return read(0x0100 + tmp);
}

void R6502::pushStack(uint8_t byte) {
  write(0x0100 + sp--, byte);
}

uint8_t R6502::isZero(uint8_t byte) {
  return byte == 0x00;
}

uint8_t R6502::isZero(uint16_t doubleByte) {
  return doubleByte == 0x0000;
}

uint8_t R6502::isNegative(uint8_t byte) {
  return byte & 0x80;
}

uint8_t R6502::isNegative(uint16_t doubleByte) {
  return doubleByte & 0x0080;
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
// Useful Methods - 
// -----
uint8_t R6502::fetch() {
  fetched = read(absAddr);
  return fetched;
}

// -----
// Addressing modes - http://archive.6502.org/datasheets/rockwell_r650x_r651x.pdf
// -----


// Next byte has operand. get current pc, then increment.
uint8_t R6502::IMM() {
  absAddr = incPC();
  return 0;
}  

// Second byte has low order byte of effective address, third has higher order byte (reminder again: 6502 is little endian!!!)
// That means ABS instructions can acess all 64KB of address space.
// 2^8 = 0x100
// 2 byte addressing...
// 0x100 * 0x100 = 0x10000 (64KB)
uint8_t R6502::ABS() {
  uint16_t lo = read(incPC());
  uint16_t hi = read(incPC());
  absAddr = (hi << 8) | lo;
  return 0;
}

uint8_t R6502::ABX() {
  uint16_t lo = read(incPC());
  uint16_t hi = read(incPC());
  absAddr = (hi << 8) | lo;
  absAddr += x;
 
  // Extra cycle is needed if page boundary crossed
  return absAddr >> 8 != hi ? 1 : 0;
}


uint8_t R6502::ABY() {
  uint16_t lo = read(incPC());
  uint16_t hi = read(incPC());
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
  absAddr = read(incPC());
  return 0;
}


uint8_t R6502::ZPX() {
  absAddr = read(incPC()) + x;
  absAddr &= 0x00FF; // no paging past the zero page may occur
  return 0;
}


uint8_t R6502::ZPY() {
  absAddr = read(incPC()) + y;
  absAddr &= 0x00FF; // no paging past the zero page may occur
  return 0;
}


uint8_t R6502::REL() {
  relAddr = read(incPC());

  // if negative (MSB of lo byte == 1), set hi byte to FF since relAddr is 2 bytes, not 1 as read. This will keep the relative address negative when converted to 2 byte form.
  if (isNegative(relAddr)) {
    relAddr |= 0xFF00;
  }

  return 0;
}


uint8_t R6502::IZX() {
  uint16_t baseAddr = read(incPC());
  uint16_t loAddr = (baseAddr + x) & 0x00FF;
  uint16_t hiAddr = (baseAddr + x + 1) & 0x00FF;

  uint16_t lo = read(loAddr);
  uint16_t hi = read(hiAddr);

  absAddr = (hi << 8) | lo;

  return 0;
}


uint8_t R6502::IZY() {
  uint16_t baseAddr = read(incPC());
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
  uint8_t pointerLo = read(incPC());
  uint8_t pointerHi = read(incPC());

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
  
  // Overflow happens when both operands have the same sign but the result is a different sign.
  // 1. XNOR the 2 operands, the MSB in the result is whether or not the signs are the same.
  // 2. check if the sign of the result differs from the sign of either operand (XOR them).
  // 3. if 1 and 2 are true, over flow occured (get the sign bit of the & of 1 and 2).
  setFlag(V, (~((uint16_t) a ^ (uint16_t) fetched) & (((uint16_t)a ^ tmp)) & 0x0080));
  setFlag(C, tmp & 0xFF00);

  tmp &= 0x00FF; // Clear higher order bits for remaining flags

  setFlag(Z, isZero(tmp));
  setFlag(N, isNegative(tmp));

  a = tmp;

  return 1; // Extra cycle possible.
}

uint8_t R6502::AND() {
  // A AND M -> A
  // Flags changed: Z N
  
  fetch();
  a &= fetched;

  setFlag(Z, a == 0);
  setFlag(N, isNegative(a));

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
      doCycle();
    }
    doCycle();
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
      doCycle();
    }
    doCycle();
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
      doCycle();
    }
    doCycle();
  }

  return 0;
}

uint8_t R6502::BIT() {
  // A AND M, M7 -> N, M6 -> V
  // Flags changed: Z N V
  
  fetch();

  tmp = (a & fetched) & 0x00FF;
  
  setFlag(Z, isZero(tmp));
  setFlag(N, isNegative(fetched));
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
      doCycle();
    }
    doCycle();
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
      doCycle();
    }
    doCycle();
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
      doCycle();
    }
    doCycle();
  }

  return 0;
}

uint8_t R6502::BRK() { // Here we will be pushing to the stack. Back to the wiki and then will come back after break :sweat_smile:
  // interrupt, push PC+2, push SR
  // Flags Changed: I
  
  incPC(); // Set this up for pushing to the stack

  setFlag(I, 1);
  pushStack(pc >> 8); // Store higher order bits first
  pushStack(pc & 0x00FF); // Than lower.
  
  // https://www.masswerk.at/6502/6502_instruction_set.html#BRK
  setFlag(B, 1);
  pushStack(P); // Store status reg.
  setFlag(B, 0);

  // "$FFFE-$FFFF = IRQ/BRK vector" https://wiki.nesdev.org/w/index.php?title=CPU_memory_map
  pc = (uint16_t) read(0xFFFE) | ((uint16_t) read(0xFFFF) << 8); // https://wiki.nesdev.org/w/index.php?title=CPU_interrupts#Interrupt_hijacking
                                                                 // (Interrupt Request (IRQ)) http://archive.6502.org/datasheets/rockwell_r650x_r651x.pdf

  return 0;
}

uint8_t R6502::BVC() {
  // branch on V = 0
  // Flags changed: 

  fetch();
  
  if (getFlag(V) == 0) {
    absAddr = fetched;
    if (fetched & 0xFF00 != absAddr & 0xFF00) {
      doCycle();
    }
    doCycle();
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
      doCycle();
    }
    doCycle();
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

  setFlag(N, isNegative(tmp));
  setFlag(Z, isZero(tmp));
  setFlag(C, a >= fetched);
  return 1;
}

uint8_t R6502::CPX() {
  // X - M
  // Flags changed: N Z C
  fetch();

  tmp = ((uint16_t) x - (uint16_t) fetched) & 0x00FF;

  setFlag(N, isNegative(tmp));
  setFlag(Z, isZero(tmp));
  setFlag(C, x >= fetched);
  return 0;
}

uint8_t R6502::CPY() {
  // Y - M
  // Flags changed: N Z C
  fetch();

  tmp = ((uint16_t) y - (uint16_t) fetched) & 0x00FF;

  setFlag(N, isNegative(tmp));
  setFlag(Z, isZero(tmp));
  setFlag(C, y >= fetched);
  return 0;
}

uint8_t R6502::DEC() {
  // M - 1 -> M
  // Flags changed: Z N
  
  fetch();
  tmp = ((uint16_t) fetched - 1) & 0x00FF;

  write(absAddr, tmp);
  
  setFlag(Z, isZero(tmp));
  setFlag(N, isNegative(tmp));

  return 0;
}

uint8_t R6502::DEX() {
  // X - 1 -> X
  // Flags changed: Z N

  x--;
  
  setFlag(Z, isZero(x));
  setFlag(N, isNegative(x));

  return 0;
}

uint8_t R6502::DEY() {
  // Y - 1 -> Y
  // Flags changed: Z N

  y--;
  
  setFlag(Z, isZero(y));
  setFlag(N, isNegative(y));

  return 0;
}

uint8_t R6502::EOR() {
  // A EOR M -> A
  // Flags changed: Z N

  fetch();

  a = a ^ fetched;
  setFlag(Z, a == 0);
  setFlag(N, isNegative(a));
  return 1;
}

uint8_t R6502::INC() {
  // M + 1 -> M
  // Flags changed: Z N
  
  fetch();
  tmp = ((uint16_t) fetched + 1) & 0x00FF;

  write(absAddr, tmp);
  
  setFlag(Z, isZero(tmp));
  setFlag(N, isNegative(tmp));

  return 0;
}

uint8_t R6502::INX() {
  // X - 1 -> X
  // Flags changed: Z N

  x++;
  
  setFlag(Z, isZero(x));
  setFlag(N, isNegative(x));

  return 0;
}

uint8_t R6502::INY() {
  // Y + 1 -> Y
  // Flags changed: Z N

  y++;
  
  setFlag(Z, isZero(y));
  setFlag(N, isNegative(y));

  return 0;
}

uint8_t R6502::JMP() {
  // (PC+1) -> PCL
  // (PC+2) -> PCH
  // Flags changed:
  pc = absAddr;

  return 0;
}

uint8_t R6502::JSR() {
  // push (PC+2),
  // (PC+1) -> PCL
  // (PC+2) -> PCH
  // Flags changed:

  pc--;
  pushStack(pc >> 8);
  pushStack(pc & 0x00FF);
  pc = absAddr;
  return 0;
}

uint8_t R6502::LDA() {
  // M -> A
  // Flags changed: Z N

  fetch();
  a = fetched;
  setFlag(Z, isZero(a));
  setFlag(N, isNegative(a));
  return 1;
}

uint8_t R6502::LDX() {
  // M -> X
  // Flags changed: Z N

  fetch();
  x = fetched;
  setFlag(Z, isZero(x));
  setFlag(N, isNegative(x));
  return 1;
}

uint8_t R6502::LDY() {
  // M -> Y
  // Flags changed: Z N

  fetch();
  y = fetched;
  setFlag(Z, isZero(y));
  setFlag(N, isNegative(y));
  return 1;
}

uint8_t R6502::LSR() {
  // 0 -> [76543210] -> C
  // Flags changed: Z N C
  
  fetch();
  
  tmp = (uint16_t) fetched >> 1;

  setFlag(C, tmp & 0xFF00);
  setFlag(Z, isZero(tmp));
  setFlag(N, 0);

  if (instructionMatrix[opcode].addressMode == &R6502::IMP) { // Implied is same as accumulator addressing mode technically.
    a = tmp & 0x00FF;
  } else {
    write(absAddr, tmp & 0x00FF);
  }

  return 0;
}

uint8_t R6502::NOP() {
  // No operation.
  // Flags changed: 
  return 0;
}

uint8_t R6502::ORA() {
  // A OR M -> A
  // Flags changed: Z N
  
  fetch();

  a = a | fetched;

  setFlag(Z, isZero(a));
  setFlag(N, isNegative(a));

  return 1;
}

uint8_t R6502::PHA() {
  // push A
  // Flags changed:
  
  pushStack(a);

  return 0;
}

uint8_t R6502::PHP() {
  // push P
  // Flags changed:
  
  pushStack(P);

  return 0;
}

uint8_t R6502::PLA() {
  // pull A
  // Flags changed: Z N

  a = pullStack();
  setFlag(Z, isZero(a));
  setFlag(N, isNegative(a));

  return 0;
}

uint8_t R6502::PLP() {
  // pull P
  // Flags changed: FROM STACK

  P = pullStack();

  return 0;
}

uint8_t R6502::ROL() {
  // C <- [76543210] <- C
  // Flags Changed: C Z N
  
  fetch();

  tmp = ((uint16_t) (fetched << 1) | (uint16_t) (fetched >> 7)) & 0x00FF;

  setFlag(C, fetched & 0x80);
  setFlag(Z, tmp == 0);
  setFlag(N, isNegative(tmp));
  
  if (instructionMatrix[opcode].addressMode == &R6502::IMP) {
     a = tmp;
  } else {
     write(absAddr, tmp);
  }

  return 0;
}

uint8_t R6502::ROR() {
  // C -> [76543210] -> C
  // Flags Changed: C Z N
  
  fetch();

  tmp = ((uint16_t) (fetched >> 1) | (uint16_t) (fetched << 7)) & 0x00FF;

  setFlag(C, fetched & 0x01);
  setFlag(Z, tmp == 0);
  setFlag(N, isNegative(tmp));
  
  if (instructionMatrix[opcode].addressMode == &R6502::IMP) {
     a = tmp;
  } else {
     write(absAddr, tmp);
  }

  return 0;
}

uint8_t R6502::RTI() {
  // pull P, pull PC
  // Flags changed: FROM STACK
  
  P = pullStack();
  pc = pullStack();

  return 0;
}

uint8_t R6502::RTS() {
  // pull PC, PC+1 -> PC
  pc = pullStack() + 1;

  return 0;
}

uint8_t R6502::SBC() {
  // A - M - (1 - C) -> A
  // C is a single bit. 1 - C is the inverse of C (C(bar)).
  // A - M - (1 - C) == A + (-M - (1 - C)) == A + (-M - 1 + C)
  // The -M and -1 Cancel because 2's complement
  // If M = 010, then -M = 110
  // -M - 1 = 101
  // M is simply inverted and we can remove the -1
  // A + (~M) + C
  // Flags changed: V C Z N
  
  fetch();

  // Same as addition, but invert memory

  tmp = (uint16_t) a + (uint16_t) (fetched ^ 0xFF) + (uint16_t) getFlag(C);

  setFlag(V, (~((uint16_t) a ^ (uint16_t) fetched) & (((uint16_t)a ^ tmp)) & 0x0080));
  setFlag(C, tmp & 0xFF00);

  tmp &= 0x00FF;

  setFlag(Z, isZero(tmp));
  setFlag(N, isNegative(tmp));

  a = tmp;

  return 1;
}

uint8_t R6502::SEC() {
  // 1 -> C
  // Flags changed: C

  setFlag(C, 1);

  return 0;
}

uint8_t R6502::SED() {
  // 1 -> D
  // Flags changed: D

  setFlag(D, 1);

  return 0;
}

uint8_t R6502::SEI() {
  // 1 -> I
  // Flags changed: I

  setFlag(I, 1);

  return 0;
}

uint8_t R6502::STA() {
  // A -> M
  // Flags changed: 

  write(absAddr, a);

  return 0;
}

uint8_t R6502::STX() {
  // X -> M
  // Flags changed: 

  write(absAddr, x);

  return 0;
}

uint8_t R6502::STY() {
  // Y -> M
  // Flags changed: 

  write(absAddr, y);

  return 0;
}

uint8_t R6502::TAX() {
  // A -> X
  // Flags changed: Z N

  x = a;

  setFlag(Z, isZero(x));
  setFlag(N, isNegative(x));

  return 0;
}

uint8_t R6502::TAY() {
  // A -> Y
  // Flags changed: Z N

  y = a;

  setFlag(Z, isZero(y));
  setFlag(N, isNegative(y));

  return 0;
}

uint8_t R6502::TSX() {
  // SP -> X
  // Flags changed: Z N

  x = sp;

  setFlag(Z, isZero(x));
  setFlag(N, isNegative(x));

  return 0;
}

uint8_t R6502::TXA() {
  // X -> A
  // Flags changed: Z N

  a = x;

  setFlag(Z, isZero(a));
  setFlag(N, isNegative(a));

  return 0;
}

uint8_t R6502::TXS() {
  // X -> SP
  // Flags changed: Z N

  sp = x;

  setFlag(Z, isZero(sp));
  setFlag(N, isNegative(sp));

  return 0;
}

uint8_t R6502::TYA() {
  // Y -> A
  // Flags changed: Z N

  a = y;

  setFlag(Z, isZero(a));
  setFlag(N, isNegative(a));

  return 0;
}









uint8_t R6502::XXX() { // Does nothing, illegal instruction
  return 0;
}




