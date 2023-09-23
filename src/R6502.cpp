#include "NESIncludes.h"

// -----
// External event functions
// -----

R6502::R6502(Memory& mem) : memory(mem) {
  // Generated using script located at util/generate-matrix.sh
  instructionMatrix =
  {
        /* 0                               1                               2                               3                               4                               5                               6                               7                               8                               9                               A                               B                               C                               D                               E                               F                               */
/* 0 */    { &R6502::IMP, &R6502::BRK, 7}, { &R6502::IZX, &R6502::ORA, 6}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::ZP0, &R6502::ORA, 3}, { &R6502::ZP0, &R6502::ASL, 5}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::IMP, &R6502::PHP, 3}, { &R6502::IMM, &R6502::ORA, 2}, { &R6502::ACC, &R6502::ASL, 2}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::ABS, &R6502::ORA, 4}, { &R6502::ABS, &R6502::ASL, 6}, { &R6502::XXX, &R6502::XXX, 0}, 
/* 1 */    { &R6502::REL, &R6502::BPL, 2}, { &R6502::IZY, &R6502::ORA, 5}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::ZPX, &R6502::ORA, 4}, { &R6502::ZPX, &R6502::ASL, 6}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::IMP, &R6502::CLC, 2}, { &R6502::ABY, &R6502::ORA, 4}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::ABX, &R6502::ORA, 4}, { &R6502::ABX, &R6502::ASL, 7}, { &R6502::XXX, &R6502::XXX, 0}, 
/* 2 */    { &R6502::XXX, &R6502::JSR, 6}, { &R6502::IZX, &R6502::AND, 6}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::ZP0, &R6502::BIT, 3}, { &R6502::ZP0, &R6502::AND, 3}, { &R6502::ZP0, &R6502::ROL, 5}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::IMP, &R6502::PLP, 4}, { &R6502::IMM, &R6502::AND, 2}, { &R6502::ACC, &R6502::ROL, 2}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::ABS, &R6502::BIT, 4}, { &R6502::ABS, &R6502::AND, 4}, { &R6502::ABS, &R6502::ROL, 6}, { &R6502::XXX, &R6502::XXX, 0}, 
/* 3 */    { &R6502::REL, &R6502::BMI, 2}, { &R6502::IZY, &R6502::AND, 5}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::ZPX, &R6502::AND, 4}, { &R6502::ZPX, &R6502::ROL, 6}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::IMP, &R6502::SEC, 2}, { &R6502::ABY, &R6502::AND, 4}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::ABX, &R6502::AND, 4}, { &R6502::ABX, &R6502::ROL, 7}, { &R6502::XXX, &R6502::XXX, 0}, 
/* 4 */    { &R6502::IMP, &R6502::RTI, 6}, { &R6502::IZX, &R6502::EOR, 6}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::ZP0, &R6502::EOR, 3}, { &R6502::ZP0, &R6502::LSR, 5}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::IMP, &R6502::PHA, 3}, { &R6502::IMM, &R6502::EOR, 2}, { &R6502::ACC, &R6502::LSR, 2}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::ABS, &R6502::JMP, 3}, { &R6502::ABS, &R6502::EOR, 4}, { &R6502::ABS, &R6502::LSR, 6}, { &R6502::XXX, &R6502::XXX, 0}, 
/* 5 */    { &R6502::REL, &R6502::BVC, 2}, { &R6502::IZY, &R6502::EOR, 5}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::ZPX, &R6502::EOR, 4}, { &R6502::ZPX, &R6502::LSR, 6}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::IMP, &R6502::CLI, 2}, { &R6502::ABY, &R6502::EOR, 4}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::ABX, &R6502::EOR, 4}, { &R6502::ABX, &R6502::LSR, 7}, { &R6502::XXX, &R6502::XXX, 0}, 
/* 6 */    { &R6502::IMP, &R6502::RTS, 6}, { &R6502::IZX, &R6502::ADC, 6}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::ZP0, &R6502::ADC, 3}, { &R6502::ZP0, &R6502::ROR, 5}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::IMP, &R6502::PLA, 4}, { &R6502::IMM, &R6502::ADC, 2}, { &R6502::ACC, &R6502::ROR, 2}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::JMP, 5}, { &R6502::ABS, &R6502::ADC, 4}, { &R6502::ABS, &R6502::ROR, 6}, { &R6502::XXX, &R6502::XXX, 0}, 
/* 7 */    { &R6502::REL, &R6502::BVS, 2}, { &R6502::IZY, &R6502::ADC, 5}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::ZPX, &R6502::ADC, 4}, { &R6502::ZPX, &R6502::ROR, 6}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::IMP, &R6502::SEI, 2}, { &R6502::ABY, &R6502::ADC, 4}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::ABX, &R6502::ADC, 4}, { &R6502::ABX, &R6502::ROR, 7}, { &R6502::XXX, &R6502::XXX, 0}, 
/* 8 */    { &R6502::XXX, &R6502::XXX, 0}, { &R6502::IZX, &R6502::STA, 6}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::ZP0, &R6502::STY, 3}, { &R6502::ZP0, &R6502::STA, 3}, { &R6502::ZP0, &R6502::STX, 3}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::IMP, &R6502::DEY, 2}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::IMP, &R6502::TXA, 2}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::ABS, &R6502::STY, 4}, { &R6502::ABS, &R6502::STA, 4}, { &R6502::ABS, &R6502::STX, 4}, { &R6502::XXX, &R6502::XXX, 0}, 
/* 9 */    { &R6502::REL, &R6502::BCC, 2}, { &R6502::IZY, &R6502::STA, 6}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::ZPX, &R6502::STY, 4}, { &R6502::ZPX, &R6502::STA, 4}, { &R6502::ZPY, &R6502::STX, 4}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::IMP, &R6502::TYA, 2}, { &R6502::ABY, &R6502::STA, 5}, { &R6502::IMP, &R6502::TXS, 2}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::ABX, &R6502::STA, 5}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, 
/* A */    { &R6502::IMM, &R6502::LDY, 2}, { &R6502::IZX, &R6502::LDA, 6}, { &R6502::IMM, &R6502::LDX, 2}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::ZP0, &R6502::LDY, 3}, { &R6502::ZP0, &R6502::LDA, 3}, { &R6502::ZP0, &R6502::LDX, 3}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::IMP, &R6502::TAY, 2}, { &R6502::IMM, &R6502::LDA, 2}, { &R6502::IMP, &R6502::TAX, 2}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::ABS, &R6502::LDY, 4}, { &R6502::ABS, &R6502::LDA, 4}, { &R6502::ABS, &R6502::LDX, 4}, { &R6502::XXX, &R6502::XXX, 0}, 
/* B */    { &R6502::REL, &R6502::BCS, 2}, { &R6502::IZY, &R6502::LDA, 5}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::ZPX, &R6502::LDY, 4}, { &R6502::ZPX, &R6502::LDA, 4}, { &R6502::ZPY, &R6502::LDX, 4}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::IMP, &R6502::CLV, 2}, { &R6502::ABY, &R6502::LDA, 4}, { &R6502::IMP, &R6502::TSX, 2}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::ABX, &R6502::LDY, 4}, { &R6502::ABX, &R6502::LDA, 4}, { &R6502::ABY, &R6502::LDX, 4}, { &R6502::XXX, &R6502::XXX, 0}, 
/* C */    { &R6502::IMM, &R6502::CPY, 2}, { &R6502::IZX, &R6502::CMP, 6}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::ZP0, &R6502::CPY, 3}, { &R6502::ZP0, &R6502::CMP, 3}, { &R6502::ZP0, &R6502::DEC, 5}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::IMP, &R6502::INY, 2}, { &R6502::IMM, &R6502::CMP, 2}, { &R6502::IMP, &R6502::DEX, 2}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::ABS, &R6502::CPY, 4}, { &R6502::ABS, &R6502::CMP, 4}, { &R6502::ABS, &R6502::DEC, 6}, { &R6502::XXX, &R6502::XXX, 0}, 
/* D */    { &R6502::REL, &R6502::BNE, 2}, { &R6502::IZY, &R6502::CMP, 5}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::ZPX, &R6502::CMP, 4}, { &R6502::ZPX, &R6502::DEC, 6}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::IMP, &R6502::CLD, 2}, { &R6502::ABY, &R6502::CMP, 4}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::ABX, &R6502::CMP, 4}, { &R6502::ABX, &R6502::DEC, 7}, { &R6502::XXX, &R6502::XXX, 0}, 
/* E */    { &R6502::IMM, &R6502::CPX, 2}, { &R6502::IZX, &R6502::SBC, 6}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::ZP0, &R6502::CPX, 3}, { &R6502::ZP0, &R6502::SBC, 3}, { &R6502::ZP0, &R6502::INC, 5}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::IMP, &R6502::INX, 2}, { &R6502::IMM, &R6502::SBC, 2}, { &R6502::IMP, &R6502::NOP, 2}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::ABS, &R6502::CPX, 4}, { &R6502::ABS, &R6502::SBC, 4}, { &R6502::ABS, &R6502::INC, 6}, { &R6502::XXX, &R6502::XXX, 0}, 
/* F */    { &R6502::REL, &R6502::BEQ, 2}, { &R6502::IZY, &R6502::SBC, 5}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::ZPX, &R6502::SBC, 4}, { &R6502::ZPX, &R6502::INC, 6}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::IMP, &R6502::SED, 2}, { &R6502::ABY, &R6502::SBC, 4}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::XXX, &R6502::XXX, 0}, { &R6502::ABX, &R6502::SBC, 4}, { &R6502::ABX, &R6502::INC, 7}, { &R6502::XXX, &R6502::XXX, 0} 
  };
}

R6502::~R6502() { }


/**
 * @brief Executes when a cycle occurs.
 * 
 * Good for capturing clock cycles.
 * 
 */
void R6502::doCycle() {
  // https://wiki.nesdev.org/w/index.php?title=Cycle_counting
  cycles++; // This won't be needed because of this function. Remove later, but keep for now so I can actually visualize what I'm changing.
  totalCyclesPassed++;
}

/**
 * @brief Performs relative branching.
 * 
 * Very frequent operation in instructions...
 * Useful method for cutting down on bugs.
 * 
 */
void R6502::doRelBranch() {
  doCycle(); // default cycle....
  absAddr = pc + relAddr;
  if (absAddr & 0xFF00 != absAddr & 0xFF00) {
    doCycle(); // branch on different page, so extra cycle
  }

  setPC(absAddr);
}

/**
 * @brief Preps an extra cycle if asked by address mode
 * 
 * Extra cycle will execute if instruction agrees on extra cycle.
 * 
 */
void R6502::prepExtraCycle() {
  extraCyclePrepped = 0x01;
}


/**
 * @brief Performs extra clock cycle if agreed upon by the address mode.
 * 
 */
void R6502::doPossibleExtraCycle() {
  if (extraCyclePrepped) doCycle();
  extraCyclePrepped = 0x00;
}

/**
 * @brief Start CPU clock.
 * 
 */
void R6502::clock() { }

/**
 * @brief Init CPU for emulation
 * 
 */
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

  RES();
}

/**
 * @brief Reset command.
 * 
 * https://wiki.nesdev.org/w/index.php?title=CPU_power_up_state
 * (Page 2 under RESET (RES)) http://archive.6502.org/datasheets/rockwell_r650x_r651x.pdf
 * 
 */
void R6502::RES() {
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

/**
 * @brief IRQ interrupt sequence command
 * 
 * http://archive.6502.org/datasheets/synertek_programming_manual.pdf - p. 131
 * https://www.nesdev.org/wiki/CPU_interrupts
 * 
 */
void R6502::IRQ() {
  pushStack16(pc);
  pushStack(P & ~B);
  setFlags(I); // B flag is cleared when pushed.
  setPC((uint16_t) read(0xFFFE) | (uint16_t) read(0xFFFF) << 8); // lo byte, than hi. C order of evalutation. Left expression first (lo).
}

/**
 * @brief NMI interrupt sequence command
 * 
 * http://archive.6502.org/datasheets/synertek_programming_manual.pdf - p. 131
 * https://www.nesdev.org/wiki/CPU_interrupts
 * 
 */
void R6502::NMI() {
  pushStack16(pc);
  pushStack(P & ~B);
  setFlags(I); // B flag is cleared when pushed.
  setPC((uint16_t) read(0xFFFA) | (uint16_t) read(0xFFFB) << 8); // lo byte, than hi. C order of evalutation. Left expression first (lo).
}

/**
 * @brief Read byte at address
 * 
 * @param addr Address of data
 * @return uint8_t The data
 */
uint8_t R6502::read(uint16_t addr) {
  //doCycle(); eventually, we'll count cy to onecles naturally. For now.... quick mafs
  memory.read(addr);
  return memory.read(addr); 
}

/**
 * @brief Read byte at address in PC and then increment PC
 * 
 * @return uint8_t The data
 */
uint8_t R6502::readPC() {
  //doCycle(); eventually, we'll count cycles naturally. For now.... quick mafs
  uint8_t byte = read(pc);
  incPC();
  return byte; 
}

/**
 * @brief Read a double byte and handle the 6502's little endian nature.
 * 
 * @param addr Initial address of double byte.
 * @return uint16_t The double byte.
 */
uint16_t R6502::read16(uint16_t addr) {
  //doCycle(); eventually, we'll count cycles naturally. For now.... quick mafs
  return ((uint16_t) (memory.read(addr + 1) << 8)) | memory.read(addr); 
}

/**
 * @brief Read byte at address in PC, increment PC, and then repeat again for the double byte.
 * 
 * @return uint16_t The double byte.
 */
uint16_t R6502::readPC16() {
  uint16_t lo = (uint16_t) readPC();
  uint16_t hi = (uint16_t) readPC();

  return (hi << 8) | lo;
}

/**
 * @brief Write a byte at an address.
 * 
 * @param addr The address to write to.
 * @param data The data to write.
 */

void R6502::write(uint16_t addr, uint8_t data) {
  //doCycle(); eventually, we'll count cycles naturally. For now.... quick mafs
  memory.write(addr, data);
}

/**
 * @brief Set the value in the PC directly.
 * 
 * @param addr The address to store in the PC.
 */
void R6502::setPC(uint16_t addr) {
  pc = addr;
  onRegisterUpdate();
}

/**
 * @brief Increment PC.
 * 
 */
void R6502::incPC() {
  setPC(pc + 1);
}

/**
 * @brief Decrement the PC.
 * 
 */
void R6502::decPC() {
  setPC(pc - 1);
}

/**
 * @brief Set the stack pointer directly.
 * 
 * @param byte New pointer value. 
 */
void R6502::setSP(uint8_t byte) {
  sp = byte;
  onRegisterUpdate();
}

/**
 * @brief Increment stack pointer.
 * 
 */
void R6502::incSP() {
  setSP(sp + 1);
}

/**
 * @brief Decrement stack pointer.
 * 
 */
void R6502::decSP() {
  setSP(sp - 1);
}

/**
 * @brief Set the X index register value directly.
 * 
 * @param byte New X index value.
 */
void R6502::setX(uint8_t byte) {
  x = byte;
  onRegisterUpdate();
}

/**
 * @brief Increment the X index register.
 * 
 */
void R6502::incX() {
  setX(x + 1);
}

/**
 * @brief Decrement the X index register.
 * 
 */
void R6502::decX() {
  setX(x - 1);
}

/**
 * @brief Set the Y index register directly.
 * 
 * @param byte New Y index value.
 */
void R6502::setY(uint8_t byte) {
  y = byte;
  onRegisterUpdate();
}

/**
 * @brief Increment the Y index register.
 * 
 */
void R6502::incY() {
  setY(y + 1);
}

/**
 * @brief Decrement the Y index register.
 * 
 */
void R6502::decY() {
  setY(y - 1);
}

/**
 * @brief Set the value of the accumulator.
 * 
 * @param byte New accumulator value.
 */
void R6502::setAccumulator(uint8_t byte) {
  accumulator = byte;
  onRegisterUpdate();
}

/**
 * @brief Set processor status directly.
 * 
 * @param byte New processor status.
 */
void R6502::setP(uint8_t byte) {
  P = byte | U;
  onRegisterUpdate();
}

/**
 * @brief Pull the stack.
 * 
 * @return uint8_t Top value on stack.
 */
uint8_t R6502::pullStack() {
  incSP();
  return read(0x0100 + sp);
}

/**
 * @brief Pull a double byute from the stack (2 pulls).
 * 
 * @return uint16_t The double byte on the stack.
 */
uint16_t R6502::pullStack16() {
  uint16_t lo = (uint16_t) pullStack();
  uint16_t hi = (uint16_t) pullStack();
  return (hi << 8) | lo;
}

/**
 * @brief Push byte onto the stack.
 * 
 * @param byte The value to push to the stack.
 */
void R6502::pushStack(uint8_t byte) {
  write(0x0100 + sp, byte);
  decSP();
}

/**
 * @brief Push double byte to the stack.
 * 
 * @param dbyte The double byte to push to the stack.
 */
void R6502::pushStack16(uint16_t dbyte) {
  pushStack(dbyte >> 8); // Store higher order bits first
  pushStack(dbyte & 0x00FF); // Than lower.
  // its cause of the way stacks work. we want to fetch lo off the stack first.
}


// -------------
// Flag utils
// -------------

/**
 * @brief Is byte a zero?
 * 
 * @param byte 
 * @return uint8_t - Returns the Zero flag (true) if zero and zero (false) if not zero.
 */
uint8_t R6502::isZero(uint8_t byte) {
  return byte == 0x00 ? Z : 0x0;
}

/**
 * @brief Is double byte a zero?
 * 
 * @param byte 
 * @return uint8_t - Returns the Zero flag (true) if zero and zero (false) if not zero.
 */
uint8_t R6502::isZero(uint16_t doubleByte) {
  return doubleByte == 0x0000 ? Z : 0x0;
}

/**
 * @brief Is byte negative?
 * 
 * @param byte 
 * @return uint8_t - Returns the Negative flag (true) if negative and zero (false) if not negative.
 */
uint8_t R6502::isNegative(uint8_t byte) {
  return byte & 0x80 ? N : 0x0;
}

/**
 * @brief Is double byte negative?
 * 
 * @param byte 
 * @return uint8_t - Returns the Negative flag (true) if negative and zero (false) if not negative.
 */
uint8_t R6502::isNegative(uint16_t doubleByte) {
  return doubleByte & 0x0080 ? N : 0x0;
}

/**
 * @brief Is double byte indicative of a carry occuring?
 * 
 * @param byte 
 * @return uint8_t - Returns the Carry flag (true) if a carry occured and zero (false) if no carry occured.
 */
uint8_t R6502::isCarry(uint16_t doubleByte) {
  return doubleByte & 0xFF00 ? C : 0x0;
}

/**
 * @brief returns the BIT value of a flag
 * 
 * @param flag The flag of the bit you want.
 * @return uint8_t 1 or 0.
 */
uint8_t R6502::getFlag(FLAGS flag) {
  return flag & P > 0 ? 1 : 0;
}

/**
 * @brief sets bits of a byte based on a mask byte and a byte representing what to change them to.
 * 
 * @param bitsToChange The byte mask.
 * @param value The values to set the bits specified by the mask to.
 * @param byte The original byte to modify.
 * @return uint8_t 
 */
uint8_t R6502::setBitsOfByte(uint8_t bitsToChange, uint8_t value, uint8_t byte) {
  return (byte & ~bitsToChange) | (value & bitsToChange);
}

/**
 * @brief Sets flags to a specific value.
 * 
 * @param flags The flags to set. e.g. Z | N | C to set the Z, N, and C flags.
 * @param value The value to set them to. i.e. 1 or 0
 */
void R6502::setFlags(uint8_t flags, uint8_t value) {
  setP(setBitsOfByte(flags, value, P));
}

/**
 * @brief Set specific flags to 1.
 * 
 * @param flags The flags to set. e.g. Z | N | C to set the Z, N, and C flags to one.
 */
void R6502::setFlags(uint8_t flags) {
  setFlags(flags, flags);
}

// -----
// Intructions utils.
// -----

/**
 * @brief Reads from the currently relevant absolute address.
 * 
 * This is almost always the operand of an instruction)
 * 
 * @return uint8_t - The operand in most cases. 
 */
uint8_t R6502::fetchOperand() {
  operand = read(absAddr);
  return operand;
}



// -----
// "Emulation hooking utils"
// -----

/**
 * @brief Called everytime a register updates.
 * 
 * Useful for logging.
 * 
 */
void R6502::onRegisterUpdate() {
  // Logging...
  return;
}

// -----
// Addressing modes - http://archive.6502.org/datasheets/rockwell_r650x_r651x.pdf
// -----


/**
 * @brief Immediate addressing mode.
 *
 * Next byte has operand. get current pc, then increment.
 * 
 */
void R6502::IMM() {
  absAddr = pc;
  incPC();
}  

/**
 * @brief Absolute addressing mode.
 * 
 * Second byte has low order byte of effective address, third has higher order byte (reminder again: 6502 is little endian!!!)
 * That means ABS instructions can acess all 64KB of address space.
 * 2^8 = 0x100
 * 2 byte addressing...
 * 0x100 * 0x100 = 0x10000 (64KB)
 *
 */
void R6502::ABS() {
  absAddr = readPC16();
}

/**
 * @brief Absolute X addressing mode.
 * 
 */
void R6502::ABX() {
  absAddr = readPC16();
  uint8_t hi = absAddr >> 8;
  absAddr += x;
 
  // Extra cycle is needed if page boundary crossed
  if (absAddr >> 8 != hi) prepExtraCycle();
}

/**
 * @brief Absolute Y addressing mode.
 * 
 */
void R6502::ABY() {
  absAddr = readPC16();
  uint8_t hi = absAddr >> 8;
  absAddr += y;
 
  // Extra cycle is needed if page boundary crossed
  if (absAddr >> 8 != hi) prepExtraCycle();
}

/**
 * @brief Implied addressing mode.
 * 
 */
void R6502::IMP() {
  operand = accumulator;
}

/**
 * @brief Accumulator addressing mode.
 * 
 * It's just IMP...
 * 
 */
void R6502::ACC() {
  IMP();
}

/**
 * @brief Zero Page addressing mode.
 * 
 * @return uint8_t Extra cycle possible?
 */
void R6502::ZP0() {
  absAddr = readPC();
}

/**
 * @brief Zero Page (X-indexed) addressing mode.
 * 
 */
void R6502::ZPX() {
  absAddr = readPC() + x;
  absAddr &= 0x00FF; // no paging past the zero page may occur
}

/**
 * @brief Zero Page (Y-indexed) addressing mode.
 * 
 */
void R6502::ZPY() {
  absAddr = readPC() + y;
  absAddr &= 0x00FF; // no paging past the zero page may occur
}

/**
 * @brief Relative addressing mode.
 * 
 */
void R6502::REL() {
  relAddr = readPC();
  // if negative (MSB of lo byte == 1), set hi byte to FF since relAddr is 2 bytes, not 1 as read. This will keep the relative address negative when converted to 2 byte form.
  if (isNegative(relAddr)) relAddr |= 0xFF00;
}

/**
 * @brief Indirect (X-indexed) addressing mode.
 * 
 */
void R6502::IZX() {
  uint16_t baseAddr = readPC();
  uint16_t loAddr = (baseAddr + x) & 0x00FF;
  absAddr = read16(loAddr);
}

/**
 * @brief Indirect (X-indexed) addressing mode.
 * 
 */
void R6502::IZY() {
  uint16_t baseAddr = readPC();
  absAddr = read16(baseAddr & 0x00FF);
  uint8_t hi = absAddr >> 8;
  absAddr += y;

  if (absAddr >> 8 != hi) prepExtraCycle();
}

/**
 * @brief Indirect addressing mode.
 * 
 * Things start to look weird here in order to simulate a bug in the CPU.
 * From hnesdev.icequake.net/6502bugs.txt:
 * "An indirect JMP (xxFF) will fail because the MSB will be fetched from
 * address xx00 instead of page xx+1."
 * DO NOT simplify this. Need to make the bug clear and show details.
 *
 */
void R6502::IND() {
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
}





// -----
// Instructions - https://www.masswerk.at/6502/6502_instruction_set.html
// -----



void R6502::ADC() {
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

  doPossibleExtraCycle();
}

void R6502::AND() {
  // A AND M -> A
  // Flags changed: Z N
  
  fetchOperand();
  setAccumulator(accumulator & operand);

  setFlags(Z | N, isZero(accumulator) | isNegative(accumulator));

  doPossibleExtraCycle();
}

void R6502::ASL() {
  // C <- [76543210] <- 0
  // Flags changed: C Z N
  
  fetchOperand();
  
  tmp = (uint16_t) operand << 1;

  setFlags(C | Z | N, isCarry(tmp) | isZero(tmp) | isNegative(tmp));

  if (instructionMatrix[opcode].addressMode == &R6502::ACC) setAccumulator(tmp & 0x00FF);
  else write(absAddr, tmp & 0x00FF);
}

void R6502::BCC() {
  // branch on C = 0
  // Flags changed: 

  if (getFlag(C) == 0) doRelBranch();
}

void R6502::BCS() {
  // branch on C = 1
  // Flags changed: 

  if (getFlag(C) == 1) doRelBranch();
}

void R6502::BEQ() {
  // branch on Z = 1
  // Flags changed: 

  if (getFlag(Z) == 1) doRelBranch();
}

void R6502::BIT() {
  // A AND M, M7 -> N, M6 -> V
  // Flags changed: Z N V
  
  fetchOperand();

  tmp = (accumulator & operand);
  
  setFlags(Z | N | V, isZero(tmp) | isNegative(operand) | (operand & (1 << 6)));
}

void R6502::BMI() {
  // branch on N = 1
  // Flags changed: 

  fetchOperand();
  
  if (getFlag(N) == 1) doRelBranch();
}

void R6502::BNE() {
  // branch on Z = 0
  // Flags changed: 

  fetchOperand();
  
  if (getFlag(Z) == 0) doRelBranch();
}

void R6502::BPL() {
  // branch on N = 0
  // Flags changed: 

  fetchOperand();
  
  if (getFlag(N) == 0) doRelBranch();
}

void R6502::BRK() { // Here we will be pushing to the stack. Back to the wiki and then will come back after break :sweat_smile:
  // interrupt, push PC+2, push SR
  // Flags Changed: I
  
  // https://www.pagetable.com/?p=410
  // http://archive.6502.org/datasheets/synertek_programming_manual.pdf - p. 131
  incPC();

  pushStack16(pc);
  // https://www.masswerk.at/6502/6502_instruction_set.html#BRK
  pushStack(P | B); // Store status reg.
  setFlags(I);

  // https://wiki.nesdev.org/w/index.php?title=CPU_interrupts#Interrupt_hijacking
  // (Interrupt Request (IRQ)) http://archive.6502.org/datasheets/rockwell_r650x_r651x.pdf
  // "$FFFE-$FFFF = IRQ/BRK vector" https://wiki.nesdev.org/w/index.php?title=CPU_memory_map
  setPC((uint16_t) read(0xFFFE) | (uint16_t) read(0xFFFF) << 8); // lo byte, than hi. C order of evalutation. Left expression first (lo).
}

void R6502::BVC() {
  // branch on V = 0
  // Flags changed: 

  fetchOperand();
  
  if (getFlag(V) == 0) doRelBranch();
}

void R6502::BVS() {
  // branch on V = 1
  // Flags changed: 

  fetchOperand();
  
  if (getFlag(V) == 1) doRelBranch();
}

void R6502::CLC() {
  // 0 -> C
  // Flags changed: C
  setFlags(C, 0);
}

void R6502::CLD() {
  // 0 -> D
  // Flags changed: D
  setFlags(D, 0);
}

void R6502::CLI() {
  // 0 -> I
  // Flags changed: I
  setFlags(I, 0);
}

void R6502::CLV() {
  // 0 -> V
  // Flags changed: V
  setFlags(V, 0);
}

void R6502::CMP() {
  // A - M
  // Flags changed: N Z C
  fetchOperand();

  tmp = ((uint16_t) accumulator - (uint16_t) operand) & 0x00FF;

  setFlags(Z | N | C, isZero(tmp) | isNegative(tmp) | accumulator >= operand ? C : 0x0);
}

void R6502::CPX() {
  // X - M
  // Flags changed: N Z C
  fetchOperand();

  tmp = ((uint16_t) x - (uint16_t) operand) & 0x00FF;

  setFlags(Z | N | C, isZero(tmp) | isNegative(tmp) | x >= operand ? C : 0x0);
}

void R6502::CPY() {
  // Y - M
  // Flags changed: N Z C
  fetchOperand();

  tmp = ((uint16_t) y - (uint16_t) operand) & 0x00FF;

  setFlags(Z | N | C, isZero(tmp) | isNegative(tmp) | y >= operand ? C : 0x0);
}

void R6502::DEC() {
  // M - 1 -> M
  // Flags changed: Z N
  
  fetchOperand();
  tmp = ((uint16_t) operand - 1) & 0x00FF;

  write(absAddr, tmp);
  
  setFlags(Z | N, isZero(tmp) | isNegative(tmp));
}

void R6502::DEX() {
  // X - 1 -> X
  // Flags changed: Z N

  decX();
  setFlags(Z | N, isZero(x) | isNegative(x));
}

void R6502::DEY() {
  // Y - 1 -> Y
  // Flags changed: Z N

  decY();
  setFlags(Z | N, isZero(y) | isNegative(y));
}

void R6502::EOR() {
  // A EOR M -> A
  // Flags changed: Z N

  fetchOperand();

  setAccumulator(accumulator ^ operand);
  setFlags(Z | N, isZero(accumulator) | isNegative(accumulator));

  doPossibleExtraCycle();
}

void R6502::INC() {
  // M + 1 -> M
  // Flags changed: Z N
  
  fetchOperand();
  tmp = ((uint16_t) operand + 1) & 0x00FF;

  write(absAddr, tmp);
  setFlags(Z | N, isZero(tmp) | isNegative(tmp));
}

void R6502::INX() {
  // X - 1 -> X
  // Flags changed: Z N

  incX();
  setFlags(Z | N, isZero(x) | isNegative(x));
}

void R6502::INY() {
  // Y + 1 -> Y
  // Flags changed: Z N

  incY();
  setFlags(Z | N, isZero(y) | isNegative(y));
}

void R6502::JMP() {
  // (PC+1) -> PCL
  // (PC+2) -> PCH
  // Flags changed:
  setPC(absAddr);
}

void R6502::JSR() {
  // push (PC+2),
  // (PC+1) -> PCL
  // (PC+2) -> PCH
  // Flags changed:

  decPC();
  pushStack16(pc);
  setPC(absAddr);
}

void R6502::LDA() {
  // M -> A
  // Flags changed: Z N

  fetchOperand();
  setAccumulator(operand);
  setFlags(Z | N, isZero(accumulator) | isNegative(accumulator));
  doPossibleExtraCycle();
}

void R6502::LDX() {
  // M -> X
  // Flags changed: Z N

  fetchOperand();
  setX(operand);
  setFlags(Z | N, isZero(x) | isNegative(x));
  doPossibleExtraCycle();
}

void R6502::LDY() {
  // M -> Y
  // Flags changed: Z N

  fetchOperand();
  setY(operand);
  setFlags(Z | N, isZero(y) | isNegative(y));
  doPossibleExtraCycle();
}

void R6502::LSR() {
  // 0 -> [76543210] -> C
  // Flags changed: Z N C
  
  fetchOperand();
  
  tmp = (uint16_t) operand >> 1;

  setFlags(C | Z | N, isZero(tmp) | isCarry(tmp));

  if (instructionMatrix[opcode].addressMode == &R6502::ACC) setAccumulator(tmp & 0x00FF);
  else write(absAddr, tmp & 0x00FF);
}

void R6502::NOP() {
  // No operation.
  // Flags changed: 
  return;
}

void R6502::ORA() {
  // A OR M -> A
  // Flags changed: Z N
  
  fetchOperand();

  setAccumulator(accumulator | operand);
  setFlags(Z | N, isZero(accumulator) | isNegative(accumulator));

  doPossibleExtraCycle();
}

void R6502::PHA() {
  // push A
  // Flags changed:
  
  pushStack(accumulator);
}

void R6502::PHP() {
  // push P
  // Flags changed:
  
  pushStack(P);
}

void R6502::PLA() {
  // pull A
  // Flags changed: Z N

  setAccumulator(pullStack());
  setFlags(Z | N, isZero(accumulator) | isNegative(accumulator));
}

void R6502::PLP() {
  // pull P
  // Flags changed: FROM STACK

  setP(pullStack());
}

void R6502::ROL() {
  // C <- [76543210] <- C
  // Flags Changed: C Z N
  
  fetchOperand();

  tmp = ((uint16_t) (operand << 1) | (uint16_t) (operand >> 7)) & 0x00FF;

  setFlags(C | Z | N, isZero(tmp) | isNegative(tmp) | operand & 0x80 ? C : 0x0);
  
  if (instructionMatrix[opcode].addressMode == &R6502::ACC) setAccumulator(tmp);
  else write(absAddr, tmp);
}

void R6502::ROR() {
  // C -> [76543210] -> C
  // Flags Changed: C Z N
  
  fetchOperand();

  tmp = ((uint16_t) (operand >> 1) | (uint16_t) (operand << 7)) & 0x00FF;

  setFlags(C | Z | N, isZero(tmp) | isNegative(tmp) | operand & 0x01 ? C : 0x0);
  
  if (instructionMatrix[opcode].addressMode == &R6502::ACC) setAccumulator(tmp);
  else write(absAddr, tmp);
}

void R6502::RTI() {
  // pull P, pull PC
  // Flags changed: FROM STACK
  // "The status register is pulled with the break flag
  // ...and bit 5 ignored. Then PC is pulled from the stack."
  
  setP(setBitsOfByte(U | B, P, pullStack()));
  setPC(pullStack16());
}

void R6502::RTS() {
  // pull PC, PC+1 -> PC
  setPC(pullStack16() + 1);
}

void R6502::SBC() {
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

  doPossibleExtraCycle();
}

void R6502::SEC() {
  // 1 -> C
  // Flags changed: C

  setFlags(C);
}

void R6502::SED() {
  // 1 -> D
  // Flags changed: D

  setFlags(D);
}

void R6502::SEI() {
  // 1 -> I
  // Flags changed: I

  setFlags(I);
}

void R6502::STA() {
  // A -> M
  // Flags changed: 

  write(absAddr, accumulator);
}

void R6502::STX() {
  // X -> M
  // Flags changed: 

  write(absAddr, x);
}

void R6502::STY() {
  // Y -> M
  // Flags changed: 

  write(absAddr, y);
}

void R6502::TAX() {
  // A -> X
  // Flags changed: Z N

  setX(accumulator);
  setFlags(Z | N, isZero(x) | isNegative(x));
}

void R6502::TAY() {
  // A -> Y
  // Flags changed: Z N

  setY(accumulator);
  setFlags(Z | N, isZero(y) | isNegative(y));
}

void R6502::TSX() {
  // SP -> X
  // Flags changed: Z N

  setX(sp);
  setFlags(Z | N, isZero(x) | isNegative(x));
}

void R6502::TXA() {
  // X -> A
  // Flags changed: Z N

  setAccumulator(x);
  setFlags(Z | N, isZero(accumulator) | isNegative(accumulator));
}

void R6502::TXS() {
  // X -> SP
  // Flags changed: Z N

  setSP(x);
  setFlags(Z | N, isZero(sp) | isNegative(sp));
}

void R6502::TYA() {
  // Y -> A
  // Flags changed: Z N

  setAccumulator(y);
  setFlags(Z | N, isZero(accumulator) | isNegative(accumulator));
}









void R6502::XXX() { // Does nothing, illegal instruction
  return;
}




