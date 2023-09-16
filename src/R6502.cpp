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



void R6502::doCycle() {
  // https://wiki.nesdev.org/w/index.php?title=Cycle_counting
  cycles++; // This won't be needed because of this function. Remove later, but keep for now so I can actually visualize what I'm changing.
  totalCyclesPassed++;
}

void R6502::doRelBranch() {
  doCycle(); // default cycle....
  absAddr = pc + relAddr;
  if (absAddr & 0xFF00 != absAddr & 0xFF00) {
    doCycle(); // branch on different page, so extra cycle
  }

  setPC(absAddr);
}

void R6502::clock() { }

void R6502::init() {
  // setting these manually... pre emulation stuff
  // Useful Variables
  absAddr = 0x0000;
  relAddr = 0x0000;
  operand = 0x00;
  tmp = 0x0000;

  accumulator = 0x00;
  x = 0x00;
  y = 0x00;

  reset();
}

void R6502::reset() {
  // SP is initialized to 0. // https://www.pagetable.com/?p=410
  setSP(0x00); 

  // https://wiki.nesdev.org/w/index.php?title=CPU_power_up_state
  // "After Reset"
  // A, X, Y were not affected

  // S was decremented by 3 (but nothing was written to the stack)
  // SEE ALSO https://www.pagetable.com/?p=410
  setSP(sp - 3);
 
  // The I (IRQ disable) flag was set to true (status ORed with $04)
  setP(0x00 | I);
  // And finally, the internal memory was unchanged

  // "...loads the program counter from the memory vector locations FFFC and FFFD..."
  // (Page 2 under RESET (RES)) http://archive.6502.org/datasheets/rockwell_r650x_r651x.pdf
  setPC(((uint16_t) read(0xFFFC) << 8) | ((uint16_t) read(0xFFFD)));

  // Done!
}

void R6502::brk() {
  // https://www.pagetable.com/?p=410
  // http://archive.6502.org/datasheets/synertek_programming_manual.pdf - p. 131
  incPC();
  incPC();

  pushStack((pc & 0xFF00) >> 8);
  pushStack((pc & 0x00FF));
  setFlags(I);
  pushStack(P);
  setPC((uint16_t) read(0xFFFE) | (uint16_t) read(0xFFFF) << 8); // lo byte, than hi. C order of evalutation. Left expression first (lo).
  // Look this over later
}

void R6502::irq() {
  // https://www.pagetable.com/?p=410
  // http://archive.6502.org/datasheets/synertek_programming_manual.pdf - p. 131
  incPC();
  incPC();

  pushStack((pc & 0xFF00) >> 8);
  pushStack((pc & 0x00FF));
  setFlags(B | I, I); // B flag is cleared wehn pushed.
  setPC((uint16_t) read(0xFFFE) | (uint16_t) read(0xFFFF) << 8); // lo byte, than hi. C order of evalutation. Left expression first (lo).
  // Look this over later
}

uint8_t R6502::read(uint16_t addr) {
  //doCycle(); eventually, we'll count cycles naturally. For now.... quick mafs
  return bus->read(addr); 
}

uint16_t R6502::read16(uint16_t addr) {
  //doCycle(); eventually, we'll count cycles naturally. For now.... quick mafs
  return ((uint16_t) (bus->read(addr + 1) << 8)) | bus->read(addr); 
}

void R6502::write(uint16_t addr, uint8_t data) {
  //doCycle(); eventually, we'll count cycles naturally. For now.... quick mafs
  bus->write(addr, data);
}

void R6502::setPC(uint16_t addr) {
  pc = addr;
  onRegisterUpdate();
}

void R6502::incPC() {
  setPC(pc + 1);
}

void R6502::decPC() {
  setPC(pc - 1);
}

void R6502::setSP(uint8_t byte) {
  sp = byte;
  onRegisterUpdate();
}

void R6502::incSP() {
  setSP(sp + 1);
}

void R6502::decSP() {
  setSP(sp - 1);
}

void R6502::setX(uint8_t byte) {
  x = byte;
  onRegisterUpdate();
}

void R6502::incX() {
  setX(x + 1);
}

void R6502::decX() {
  setX(x - 1);
}

void R6502::setY(uint8_t byte) {
  y = byte;
  onRegisterUpdate();
}

void R6502::incY() {
  setY(y + 1);
}

void R6502::decY() {
  setY(y - 1);
}

void R6502::setAccumulator(uint8_t byte) {
  accumulator = byte;
  onRegisterUpdate();
}

void R6502::setP(uint8_t byte) {
  P = byte | U;
  onRegisterUpdate();
}

void R6502::onRegisterUpdate() {
  // Logging...
  return;
}

uint8_t R6502::pullStack() {
  incSP();
  return read(0x0100 + sp);
}
uint16_t R6502::pullStack16() {
  uint16_t lo = (uint16_t) pullStack();
  uint16_t hi = (uint16_t) pullStack();
  return (hi << 8) | lo;
}

void R6502::pushStack(uint8_t byte) {
  write(0x0100 + sp, byte);
  decSP();
}

uint8_t R6502::isZero(uint8_t byte) {
  return byte == 0x00 ? Z : 0x0;
}

uint8_t R6502::isZero(uint16_t doubleByte) {
  return doubleByte == 0x0000 ? Z : 0x0;
}

uint8_t R6502::isNegative(uint8_t byte) {
  return byte & 0x80 ? N : 0x0;
}

uint8_t R6502::isNegative(uint16_t doubleByte) {
  return doubleByte & 0x0080 ? N : 0x0;
}

uint8_t R6502::isCarry(uint16_t doubleByte) {
  return doubleByte & 0xFF00 ? C : 0x0;
}
  
 
void R6502::connectBus(Bus * b) {
  bus = b;
}

uint8_t R6502::getFlag(FLAGS flag) {
  return flag & P > 0 ? 1 : 0;
}

uint8_t R6502::setBitsOfByte(uint8_t bitsToChange, uint8_t value, uint8_t byte) {
  return (byte & ~bitsToChange) | (value & bitsToChange);
}

void R6502::setFlags(uint8_t flags, uint8_t value) {
  setP(setBitsOfByte(flags, value, P));
}

void R6502::setFlags(uint8_t flags) {
  setFlags(flags, flags);
}

// -----
// Useful Methods - 
// -----
uint8_t R6502::fetchOperand() {
  operand = read(absAddr);
  return operand;
}

// -----
// Addressing modes - http://archive.6502.org/datasheets/rockwell_r650x_r651x.pdf
// -----


// Next byte has operand. get current pc, then increment.
uint8_t R6502::IMM() {
  absAddr = pc;
  incPC();
  return 0;
}  

// Second byte has low order byte of effective address, third has higher order byte (reminder again: 6502 is little endian!!!)
// That means ABS instructions can acess all 64KB of address space.
// 2^8 = 0x100
// 2 byte addressing...
// 0x100 * 0x100 = 0x10000 (64KB)
uint8_t R6502::ABS() {
  absAddr = read16(pc);
  setPC(pc + 2);
  return 0;
}

uint8_t R6502::ABX() {
  absAddr = read16(pc);
  uint8_t hi = absAddr >> 8;
  setPC(pc + 2);
  absAddr += x;
 
  // Extra cycle is needed if page boundary crossed
  return absAddr >> 8 != hi ? 1 : 0;
}


uint8_t R6502::ABY() {
  absAddr = read16(pc);
  uint8_t hi = absAddr >> 8;
  setPC(pc + 2);
  absAddr += y;
 
  // Extra cycle is needed if page boundary crossed
  return absAddr >> 8 != hi ? 1 : 0;
}


uint8_t R6502::IMP() {
  operand = accumulator;
  return 0;
}


uint8_t R6502::ZP0() {
  absAddr = read(pc);
  incPC();
  return 0;
}


uint8_t R6502::ZPX() {
  absAddr = read(pc) + x;
  incPC();
  absAddr &= 0x00FF; // no paging past the zero page may occur
  return 0;
}


uint8_t R6502::ZPY() {
  absAddr = read(pc) + y;
  incPC();
  absAddr &= 0x00FF; // no paging past the zero page may occur
  return 0;
}


uint8_t R6502::REL() {
  relAddr = read(pc);
  incPC();
  // if negative (MSB of lo byte == 1), set hi byte to FF since relAddr is 2 bytes, not 1 as read. This will keep the relative address negative when converted to 2 byte form.
  if (isNegative(relAddr)) {
    relAddr |= 0xFF00;
  }

  return 0;
}


uint8_t R6502::IZX() {
  uint16_t baseAddr = read(pc);
  incPC();
  uint16_t loAddr = (baseAddr + x) & 0x00FF;
  absAddr = read16(loAddr);

  return 0;
}


uint8_t R6502::IZY() {
  uint16_t baseAddr = read(pc);
  incPC();
  absAddr = read16(baseAddr & 0x00FF);
  uint8_t hi = absAddr >> 8;
  absAddr += y;

  return absAddr >> 8 != hi ? 1 : 0;
}


uint8_t R6502::IND() {
  // Things start to look weird here in order to simulate a bug in the CPU.
  // From hnesdev.icequake.net/6502bugs.txt:
  // "An indirect JMP (xxFF) will fail because the MSB will be fetched from
  // address xx00 instead of page xx+1."
  // DO NOT simplify this. Need to make the bug clear and show details.
  uint8_t pointerLo = read(pc);
  incPC();
  uint8_t pointerHi = read(pc);
  incPC();

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

  fetchOperand(); // fetch target data

  tmp = (uint16_t) accumulator + (uint16_t) operand + (uint16_t) getFlag(C);
  
  // Overflow happens when both operands have the same sign but the result is a different sign.
  // 1. XNOR the 2 operands, the MSB in the result is whether or not the signs are the same.
  // 2. check if the sign of the result differs from the sign of either operand (XOR them).
  // 3. if 1 and 2 are true, over flow occured (get the sign bit of the & of 1 and 2).
  uint8_t overflowBit = (~((uint16_t) accumulator ^ (uint16_t) operand) & (((uint16_t)accumulator ^ tmp)) & 0x0080) ? V : 0x0;

  setFlags(C | Z | N | V, isCarry(tmp) | isZero((uint8_t) (tmp & 0x00FF)) | isNegative(tmp) | overflowBit);

  setAccumulator(tmp);

  return 1;
}

uint8_t R6502::AND() {
  // A AND M -> A
  // Flags changed: Z N
  
  fetchOperand();
  setAccumulator(accumulator & operand);

  setFlags(Z | N, isZero(accumulator) | isNegative(accumulator));

  return 1;
}

uint8_t R6502::ASL() {
  // C <- [76543210] <- 0
  // Flags changed: C Z N
  
  fetchOperand();
  
  tmp = (uint16_t) operand << 1;

  setFlags(C | Z | N, isCarry(tmp) | isZero(tmp) | isNegative(tmp));

  if (instructionMatrix[opcode].addressMode == &R6502::IMP) { // Implied is same as accumulator addressing mode technically.
    setAccumulator(tmp & 0x00FF);
  } else {
    write(absAddr, tmp & 0x00FF);
  }

  return 0;
}

uint8_t R6502::BCC() {
  // branch on C = 0
  // Flags changed: 

  if (getFlag(C) == 0) doRelBranch();

  return 0;
}

uint8_t R6502::BCS() {
  // branch on C = 1
  // Flags changed: 

  if (getFlag(C) == 1) doRelBranch();

  return 0;
}

uint8_t R6502::BEQ() {
  // branch on Z = 1
  // Flags changed: 

  if (getFlag(Z) == 1) doRelBranch();

  return 0;
}

uint8_t R6502::BIT() {
  // A AND M, M7 -> N, M6 -> V
  // Flags changed: Z N V
  
  fetchOperand();

  tmp = (accumulator & operand);
  
  setFlags(Z | N | V, isZero(tmp) | isNegative(operand) | (operand & (1 << 6)));

  return 0;
}

uint8_t R6502::BMI() {
  // branch on N = 1
  // Flags changed: 

  fetchOperand();
  
  if (getFlag(N) == 1) doRelBranch();

  return 0;
}

uint8_t R6502::BNE() {
  // branch on Z = 0
  // Flags changed: 

  fetchOperand();
  
  if (getFlag(Z) == 0) doRelBranch();

  return 0;
}

uint8_t R6502::BPL() {
  // branch on N = 0
  // Flags changed: 

  fetchOperand();
  
  if (getFlag(N) == 0) doRelBranch();

  return 0;
}

uint8_t R6502::BRK() { // Here we will be pushing to the stack. Back to the wiki and then will come back after break :sweat_smile:
  // interrupt, push PC+2, push SR
  // Flags Changed: I
  
  incPC(); // Set this up for pushing to the stack

  setFlags(I);
  pushStack(pc >> 8); // Store higher order bits first
  pushStack(pc & 0x00FF); // Than lower.
  
  // https://www.masswerk.at/6502/6502_instruction_set.html#BRK
  pushStack(P | B); // Store status reg.

  // "$FFFE-$FFFF = IRQ/BRK vector" https://wiki.nesdev.org/w/index.php?title=CPU_memory_map
  setPC((uint16_t) read(0xFFFE) | ((uint16_t) read(0xFFFF) << 8)); // https://wiki.nesdev.org/w/index.php?title=CPU_interrupts#Interrupt_hijacking
                                                                 // (Interrupt Request (IRQ)) http://archive.6502.org/datasheets/rockwell_r650x_r651x.pdf

  return 0;
}

uint8_t R6502::BVC() {
  // branch on V = 0
  // Flags changed: 

  fetchOperand();
  
  if (getFlag(V) == 0) doRelBranch();

  return 0;
}

uint8_t R6502::BVS() {
  // branch on V = 1
  // Flags changed: 

  fetchOperand();
  
  if (getFlag(V) == 1) doRelBranch();

  return 0;
}

uint8_t R6502::CLC() {
  // 0 -> C
  // Flags changed: C
  setFlags(C, 0);
  return 0;
}

uint8_t R6502::CLD() {
  // 0 -> D
  // Flags changed: D
  setFlags(D, 0);
  return 0;
}

uint8_t R6502::CLI() {
  // 0 -> I
  // Flags changed: I
  setFlags(I, 0);
  return 0;
}

uint8_t R6502::CLV() {
  // 0 -> V
  // Flags changed: V
  setFlags(V, 0);
  return 0;
}

uint8_t R6502::CMP() {
  // A - M
  // Flags changed: N Z C
  fetchOperand();

  tmp = ((uint16_t) accumulator - (uint16_t) operand) & 0x00FF;

  setFlags(Z | N | C, isZero(tmp) | isNegative(tmp) | accumulator >= operand ? C : 0x0);

  return 1;
}

uint8_t R6502::CPX() {
  // X - M
  // Flags changed: N Z C
  fetchOperand();

  tmp = ((uint16_t) x - (uint16_t) operand) & 0x00FF;

  setFlags(Z | N | C, isZero(tmp) | isNegative(tmp) | x >= operand ? C : 0x0);
  return 0;
}

uint8_t R6502::CPY() {
  // Y - M
  // Flags changed: N Z C
  fetchOperand();

  tmp = ((uint16_t) y - (uint16_t) operand) & 0x00FF;

  setFlags(Z | N | C, isZero(tmp) | isNegative(tmp) | y >= operand ? C : 0x0);
  return 0;
}

uint8_t R6502::DEC() {
  // M - 1 -> M
  // Flags changed: Z N
  
  fetchOperand();
  tmp = ((uint16_t) operand - 1) & 0x00FF;

  write(absAddr, tmp);
  
  setFlags(Z | N, isZero(tmp) | isNegative(tmp));

  return 0;
}

uint8_t R6502::DEX() {
  // X - 1 -> X
  // Flags changed: Z N

  decX();
  setFlags(Z | N, isZero(x) | isNegative(x));

  return 0;
}

uint8_t R6502::DEY() {
  // Y - 1 -> Y
  // Flags changed: Z N

  decY();
  setFlags(Z | N, isZero(y) | isNegative(y));

  return 0;
}

uint8_t R6502::EOR() {
  // A EOR M -> A
  // Flags changed: Z N

  fetchOperand();

  setAccumulator(accumulator ^ operand);
  setFlags(Z | N, isZero(accumulator) | isNegative(accumulator));

  return 1;
}

uint8_t R6502::INC() {
  // M + 1 -> M
  // Flags changed: Z N
  
  fetchOperand();
  tmp = ((uint16_t) operand + 1) & 0x00FF;

  write(absAddr, tmp);
  setFlags(Z | N, isZero(tmp) | isNegative(tmp));

  return 0;
}

uint8_t R6502::INX() {
  // X - 1 -> X
  // Flags changed: Z N

  incX();
  setFlags(Z | N, isZero(x) | isNegative(x));

  return 0;
}

uint8_t R6502::INY() {
  // Y + 1 -> Y
  // Flags changed: Z N

  incY();
  setFlags(Z | N, isZero(y) | isNegative(y));

  return 0;
}

uint8_t R6502::JMP() {
  // (PC+1) -> PCL
  // (PC+2) -> PCH
  // Flags changed:
  setPC(absAddr);

  return 0;
}

uint8_t R6502::JSR() {
  // push (PC+2),
  // (PC+1) -> PCL
  // (PC+2) -> PCH
  // Flags changed:

  decPC();
  pushStack(pc >> 8);
  pushStack(pc & 0x00FF);
  setPC(absAddr);
  return 0;
}

uint8_t R6502::LDA() {
  // M -> A
  // Flags changed: Z N

  fetchOperand();
  setAccumulator(operand);
  setFlags(Z | N, isZero(accumulator) | isNegative(accumulator));
  return 1;
}

uint8_t R6502::LDX() {
  // M -> X
  // Flags changed: Z N

  fetchOperand();
  setX(operand);
  setFlags(Z | N, isZero(x) | isNegative(x));
  return 1;
}

uint8_t R6502::LDY() {
  // M -> Y
  // Flags changed: Z N

  fetchOperand();
  setY(operand);
  setFlags(Z | N, isZero(y) | isNegative(y));
  return 1;
}

uint8_t R6502::LSR() {
  // 0 -> [76543210] -> C
  // Flags changed: Z N C
  
  fetchOperand();
  
  tmp = (uint16_t) operand >> 1;

  setFlags(C | Z | N, isZero(tmp) | isCarry(tmp));

  if (instructionMatrix[opcode].addressMode == &R6502::IMP) { // Implied is same as accumulator addressing mode technically.
    setAccumulator(tmp & 0x00FF);
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
  
  fetchOperand();

  setAccumulator(accumulator | operand);
  setFlags(Z | N, isZero(accumulator) | isNegative(accumulator));

  return 1;
}

uint8_t R6502::PHA() {
  // push A
  // Flags changed:
  
  pushStack(accumulator);

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

  setAccumulator(pullStack());
  setFlags(Z | N, isZero(accumulator) | isNegative(accumulator));

  return 0;
}

uint8_t R6502::PLP() {
  // pull P
  // Flags changed: FROM STACK

  setP(pullStack());

  return 0;
}

uint8_t R6502::ROL() {
  // C <- [76543210] <- C
  // Flags Changed: C Z N
  
  fetchOperand();

  tmp = ((uint16_t) (operand << 1) | (uint16_t) (operand >> 7)) & 0x00FF;

  setFlags(C | Z | N, isZero(tmp) | isNegative(tmp) | operand & 0x80 ? C : 0x0);
  
  if (instructionMatrix[opcode].addressMode == &R6502::IMP) {
     setAccumulator(tmp);
  } else {
     write(absAddr, tmp);
  }

  return 0;
}

uint8_t R6502::ROR() {
  // C -> [76543210] -> C
  // Flags Changed: C Z N
  
  fetchOperand();

  tmp = ((uint16_t) (operand >> 1) | (uint16_t) (operand << 7)) & 0x00FF;

  setFlags(C | Z | N, isZero(tmp) | isNegative(tmp) | operand & 0x01 ? C : 0x0);
  
  if (instructionMatrix[opcode].addressMode == &R6502::IMP) {
     setAccumulator(tmp);
  } else {
     write(absAddr, tmp);
  }

  return 0;
}

uint8_t R6502::RTI() {
  // pull P, pull PC
  // Flags changed: FROM STACK
  // "The status register is pulled with the break flag
  // ...and bit 5 ignored. Then PC is pulled from the stack."
  
  setP(setBitsOfByte(U | B, P, pullStack()));

  setPC(pullStack16());

  return 0;
}

uint8_t R6502::RTS() {
  // pull PC, PC+1 -> PC
  setPC(pullStack16() + 1);

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
  
  fetchOperand();

  // Same as addition, but invert memory

  tmp = (uint16_t) accumulator + (uint16_t) (operand ^ 0xFF) + (uint16_t) getFlag(C);

  uint8_t overflowBit = (~((uint16_t) accumulator ^ (uint16_t) operand) & (((uint16_t)accumulator ^ tmp)) & 0x0080) ? V : 0;
  setFlags(V | C | Z | N, overflowBit | isCarry(tmp) | isZero(tmp) | isNegative(tmp));

  setAccumulator(tmp);

  return 1;
}

uint8_t R6502::SEC() {
  // 1 -> C
  // Flags changed: C

  setFlags(C);

  return 0;
}

uint8_t R6502::SED() {
  // 1 -> D
  // Flags changed: D

  setFlags(D);

  return 0;
}

uint8_t R6502::SEI() {
  // 1 -> I
  // Flags changed: I

  setFlags(I);

  return 0;
}

uint8_t R6502::STA() {
  // A -> M
  // Flags changed: 

  write(absAddr, accumulator);

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

  setX(accumulator);
  setFlags(Z | N, isZero(x) | isNegative(x));

  return 0;
}

uint8_t R6502::TAY() {
  // A -> Y
  // Flags changed: Z N

  setY(accumulator);
  setFlags(Z | N, isZero(y) | isNegative(y));

  return 0;
}

uint8_t R6502::TSX() {
  // SP -> X
  // Flags changed: Z N

  setX(sp);
  setFlags(Z | N, isZero(x) | isNegative(x));

  return 0;
}

uint8_t R6502::TXA() {
  // X -> A
  // Flags changed: Z N

  setAccumulator(x);
  setFlags(Z | N, isZero(accumulator) | isNegative(accumulator));

  return 0;
}

uint8_t R6502::TXS() {
  // X -> SP
  // Flags changed: Z N

  setSP(x);
  setFlags(Z | N, isZero(sp) | isNegative(sp));

  return 0;
}

uint8_t R6502::TYA() {
  // Y -> A
  // Flags changed: Z N

  setAccumulator(y);
  setFlags(Z | N, isZero(accumulator) | isNegative(accumulator));

  return 0;
}









uint8_t R6502::XXX() { // Does nothing, illegal instruction
  return 0;
}




