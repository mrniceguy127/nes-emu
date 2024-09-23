#include "NESIncludes.h"
#include <iostream>
#include <iomanip>

// -----
// External event functions
// -----

// Generated using script located at util/generate-matrix.sh
const R6502::Instruction R6502::instructionMatrix[0x100] = {
          /* 0                       1                       2                       3                       4                       5                       6                       7                       8                       9                       A                       B                       C                       D                       E                       F                       */
  /* 0 */    { IMPLIED    , BRK   }, { INDIRECTX  , ORA   }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ZEROPAGE   , ORA   }, { ZEROPAGE   , ASL   }, { ILLMODE    , ILLOP }, { IMPLIED    , PHP   }, { IMMEDIATE  , ORA   }, { ACCUMULATOR, ASL   }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ABSOLUTE   , ORA   }, { ABSOLUTE   , ASL   }, { ILLMODE    , ILLOP }, 
  /* 1 */    { RELATIVE   , BPL   }, { INDIRECTY  , ORA   }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ZEROPAGEX  , ORA   }, { ZEROPAGEX  , ASL   }, { ILLMODE    , ILLOP }, { IMPLIED    , CLC   }, { ABSOLUTEY  , ORA   }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ABSOLUTEX  , ORA   }, { ABSOLUTEX  , ASL   }, { ILLMODE    , ILLOP }, 
  /* 2 */    { ABSOLUTE   , JSR   }, { INDIRECTX  , AND   }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ZEROPAGE   , BIT   }, { ZEROPAGE   , AND   }, { ZEROPAGE   , ROL   }, { ILLMODE    , ILLOP }, { IMPLIED    , PLP   }, { IMMEDIATE  , AND   }, { ACCUMULATOR, ROL   }, { ILLMODE    , ILLOP }, { ABSOLUTE   , BIT   }, { ABSOLUTE   , AND   }, { ABSOLUTE   , ROL   }, { ILLMODE    , ILLOP }, 
  /* 3 */    { RELATIVE   , BMI   }, { INDIRECTY  , AND   }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ZEROPAGEX  , AND   }, { ZEROPAGEX  , ROL   }, { ILLMODE    , ILLOP }, { IMPLIED    , SEC   }, { ABSOLUTEY  , AND   }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ABSOLUTEX  , AND   }, { ABSOLUTEX  , ROL   }, { ILLMODE    , ILLOP }, 
  /* 4 */    { IMPLIED    , RTI   }, { INDIRECTX  , EOR   }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ZEROPAGE   , EOR   }, { ZEROPAGE   , LSR   }, { ILLMODE    , ILLOP }, { IMPLIED    , PHA   }, { IMMEDIATE  , EOR   }, { ACCUMULATOR, LSR   }, { ILLMODE    , ILLOP }, { ABSOLUTE   , JMP   }, { ABSOLUTE   , EOR   }, { ABSOLUTE   , LSR   }, { ILLMODE    , ILLOP }, 
  /* 5 */    { RELATIVE   , BVC   }, { INDIRECTY  , EOR   }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ZEROPAGEX  , EOR   }, { ZEROPAGEX  , LSR   }, { ILLMODE    , ILLOP }, { IMPLIED    , CLI   }, { ABSOLUTEY  , EOR   }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ABSOLUTEX  , EOR   }, { ABSOLUTEX  , LSR   }, { ILLMODE    , ILLOP }, 
  /* 6 */    { IMPLIED    , RTS   }, { INDIRECTX  , ADC   }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ZEROPAGE   , ADC   }, { ZEROPAGE   , ROR   }, { ILLMODE    , ILLOP }, { IMPLIED    , PLA   }, { IMMEDIATE  , ADC   }, { ACCUMULATOR, ROR   }, { ILLMODE    , ILLOP }, { INDIRECT   , JMP   }, { ABSOLUTE   , ADC   }, { ABSOLUTE   , ROR   }, { ILLMODE    , ILLOP }, 
  /* 7 */    { RELATIVE   , BVS   }, { INDIRECTY  , ADC   }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ZEROPAGEX  , ADC   }, { ZEROPAGEX  , ROR   }, { ILLMODE    , ILLOP }, { IMPLIED    , SEI   }, { ABSOLUTEY  , ADC   }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ABSOLUTEX  , ADC   }, { ABSOLUTEX  , ROR   }, { ILLMODE    , ILLOP }, 
  /* 8 */    { ILLMODE    , ILLOP }, { INDIRECTX  , STA   }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ZEROPAGE   , STY   }, { ZEROPAGE   , STA   }, { ZEROPAGE   , STX   }, { ILLMODE    , ILLOP }, { IMPLIED    , DEY   }, { ILLMODE    , ILLOP }, { IMPLIED    , TXA   }, { ILLMODE    , ILLOP }, { ABSOLUTE   , STY   }, { ABSOLUTE   , STA   }, { ABSOLUTE   , STX   }, { ILLMODE    , ILLOP }, 
  /* 9 */    { RELATIVE   , BCC   }, { INDIRECTY  , STA   }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ZEROPAGEX  , STY   }, { ZEROPAGEX  , STA   }, { ZEROPAGEY  , STX   }, { ILLMODE    , ILLOP }, { IMPLIED    , TYA   }, { ABSOLUTEY  , STA   }, { IMPLIED    , TXS   }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ABSOLUTEX  , STA   }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, 
  /* A */    { IMMEDIATE  , LDY   }, { INDIRECTX  , LDA   }, { IMMEDIATE  , LDX   }, { ILLMODE    , ILLOP }, { ZEROPAGE   , LDY   }, { ZEROPAGE   , LDA   }, { ZEROPAGE   , LDX   }, { ILLMODE    , ILLOP }, { IMPLIED    , TAY   }, { IMMEDIATE  , LDA   }, { IMPLIED    , TAX   }, { ILLMODE    , ILLOP }, { ABSOLUTE   , LDY   }, { ABSOLUTE   , LDA   }, { ABSOLUTE   , LDX   }, { ILLMODE    , ILLOP }, 
  /* B */    { RELATIVE   , BCS   }, { INDIRECTY  , LDA   }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ZEROPAGEX  , LDY   }, { ZEROPAGEX  , LDA   }, { ZEROPAGEY  , LDX   }, { ILLMODE    , ILLOP }, { IMPLIED    , CLV   }, { ABSOLUTEY  , LDA   }, { IMPLIED    , TSX   }, { ILLMODE    , ILLOP }, { ABSOLUTEX  , LDY   }, { ABSOLUTEX  , LDA   }, { ABSOLUTEY  , LDX   }, { ILLMODE    , ILLOP }, 
  /* C */    { IMMEDIATE  , CPY   }, { INDIRECTX  , CMP   }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ZEROPAGE   , CPY   }, { ZEROPAGE   , CMP   }, { ZEROPAGE   , DEC   }, { ILLMODE    , ILLOP }, { IMPLIED    , INY   }, { IMMEDIATE  , CMP   }, { IMPLIED    , DEX   }, { ILLMODE    , ILLOP }, { ABSOLUTE   , CPY   }, { ABSOLUTE   , CMP   }, { ABSOLUTE   , DEC   }, { ILLMODE    , ILLOP }, 
  /* D */    { RELATIVE   , BNE   }, { INDIRECTY  , CMP   }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ZEROPAGEX  , CMP   }, { ZEROPAGEX  , DEC   }, { ILLMODE    , ILLOP }, { IMPLIED    , CLD   }, { ABSOLUTEY  , CMP   }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ABSOLUTEX  , CMP   }, { ABSOLUTEX  , DEC   }, { ILLMODE    , ILLOP }, 
  /* E */    { IMMEDIATE  , CPX   }, { INDIRECTX  , SBC   }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ZEROPAGE   , CPX   }, { ZEROPAGE   , SBC   }, { ZEROPAGE   , INC   }, { ILLMODE    , ILLOP }, { IMPLIED    , INX   }, { IMMEDIATE  , SBC   }, { IMPLIED    , NOP   }, { ILLMODE    , ILLOP }, { ABSOLUTE   , CPX   }, { ABSOLUTE   , SBC   }, { ABSOLUTE   , INC   }, { ILLMODE    , ILLOP }, 
  /* F */    { RELATIVE   , BEQ   }, { INDIRECTY  , SBC   }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ZEROPAGEX  , SBC   }, { ZEROPAGEX  , INC   }, { ILLMODE    , ILLOP }, { IMPLIED    , SED   }, { ABSOLUTEY  , SBC   }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ILLMODE    , ILLOP }, { ABSOLUTEX  , SBC   }, { ABSOLUTEX  , INC   }, { ILLMODE    , ILLOP } 
};

R6502::R6502(Memory* mem) {
  memory = mem;
}

R6502::~R6502() { }

const R6502::Instruction R6502::NULL_INSTRUCTION = { ILLMODE, ILLOP };


R6502::State R6502::getState() {
  State state = {
    accumulator,
    x,
    y,
    pc,
    sp,
    P
  };

  return state;
}  

const char* R6502::opMnemonics[57] = {
  "ILLEGAL", // Fake emulator null mnemonic...

  "ADC", "AND", "ASL", "BCC", "BCS", "BEQ", "BIT", "BMI",
  "BNE", "BPL", "BRK", "BVC", "BVS", "CLC", "CLD", "CLI",
  "CLV", "CMP", "CPX", "CPY", "DEC", "DEX", "DEY", "EOR",
  "INC", "INX", "INY", "JMP", "JSR", "LDA", "LDX", "LDY",
  "LSR", "NOP", "ORA", "PHA", "PHP", "PLA", "PLP", "ROL",
  "ROR", "RTI", "RTS", "SBC", "SEC", "SED", "SEI", "STA",
  "STX", "STY", "TAX", "TAY", "TSX", "TXA", "TXS", "TYA"
};

const char* R6502::addressModeNames[14] = {
  "ILLEGAL", // Fake emulator null address mode...

  "IMMEDIATE",
  "ABSOLUTE", "ABSOLUTEX", "ABSOLUTEY",
  "IMPLIED", "ACCUMULATOR",
  "ZEROPAGE", "ZEROPAGEX", "ZEROPAGEY",
  "RELATIVE",
  "INDIRECT", "INDIRECTX", "INDIRECTY"
};

void R6502::doAddressMode(MODES mode) {
  switch (mode) {
    case IMMEDIATE  : modeImmediate();   break;
    case ABSOLUTE   : modeAbsolute();    break;
    case ABSOLUTEX  : modeAbsoluteX();   break;
    case ABSOLUTEY  : modeAbsoluteY();   break;
    case IMPLIED    : modeImplied();     break;
    case ACCUMULATOR: modeAccumulator(); break;
    case ZEROPAGE   : modeZeroPage();    break;
    case ZEROPAGEX  : modeZeroPageX();   break;
    case ZEROPAGEY  : modeZeroPageY();   break;
    case RELATIVE   : modeRelative();    break;
    case INDIRECT   : modeIndirect();    break;
    case INDIRECTX  : modeIndirectX();   break;
    case INDIRECTY  : modeIndirectY();   break;

    default         : modeIllegal();     break;
  }
}

void R6502::doOperation(OPS op) {
  switch (op) {
    case ADC: opADC(); break;
    case AND: opAND(); break;
    case ASL: opASL(); break;
    case BCC: opBCC(); break;
    case BCS: opBCS(); break;
    case BEQ: opBEQ(); break;
    case BIT: opBIT(); break;
    case BMI: opBMI(); break;
    case BNE: opBNE(); break;
    case BPL: opBPL(); break;
    case BRK: opBRK(); break;
    case BVC: opBVC(); break;
    case BVS: opBVS(); break;
    case CLC: opCLC(); break;
    case CLD: opCLD(); break;
    case CLI: opCLI(); break;
    case CLV: opCLV(); break;
    case CMP: opCMP(); break;
    case CPX: opCPX(); break;
    case CPY: opCPY(); break;
    case DEC: opDEC(); break;
    case DEX: opDEX(); break;
    case DEY: opDEY(); break;
    case EOR: opEOR(); break;
    case INC: opINC(); break;
    case INX: opINX(); break;
    case INY: opINY(); break;
    case JMP: opJMP(); break;
    case JSR: opJSR(); break;
    case LDA: opLDA(); break;
    case LDX: opLDX(); break;
    case LDY: opLDY(); break;
    case LSR: opLSR(); break;
    case NOP: opNOP(); break;
    case ORA: opORA(); break;
    case PHA: opPHA(); break;
    case PHP: opPHP(); break;
    case PLA: opPLA(); break;
    case PLP: opPLP(); break;
    case ROL: opROL(); break;
    case ROR: opROR(); break;
    case RTI: opRTI(); break;
    case RTS: opRTS(); break;
    case SBC: opSBC(); break;
    case SEC: opSEC(); break;
    case SED: opSED(); break;
    case SEI: opSEI(); break;
    case STA: opSTA(); break;
    case STX: opSTX(); break;
    case STY: opSTY(); break;
    case TAX: opTAX(); break;
    case TAY: opTAY(); break;
    case TSX: opTSX(); break;
    case TXA: opTXA(); break;
    case TXS: opTXS(); break;
    case TYA: opTYA(); break;

    default: opIllegal(); break;
  }
}

void R6502::doInstruction(const Instruction& instruction) {
  currentInstruction = instruction;
  doAddressMode(currentInstruction.addressMode);
  doOperation(currentInstruction.operation);
  currentInstruction = NULL_INSTRUCTION;
}

void R6502::doNextInstruction() {
  cyclesPassedThisInstruction = 0x00;
  extraCyclesPassedThisInstruction = 0x00;
  opcode = readPC();
  Instruction instruction = instructionMatrix[opcode];
  doInstruction(instruction);
}

const char* R6502::getOpMnemonic(OPS op) {
  return opMnemonics[op];
}

const char* R6502::getAddressModeName(MODES mode) {
  return addressModeNames[mode];
}

const R6502::Instruction * R6502::getInstructionMatrix() {
  return instructionMatrix;
}

R6502::InstructionMetadata R6502::getInstructionMetadata(Instruction& instruction) {
  return {
    getOpMnemonic(instruction.operation),
    getAddressModeName(instruction.addressMode)
  };
}

R6502::InstructionMetadata R6502::getInstructionMetadata(uint8_t opCode) {
  Instruction instruction = instructionMatrix[opCode];
  return getInstructionMetadata(instruction);
}

uint8_t R6502::getCurrentOpCode() {
  return opcode;
}

void R6502::doCycle() {
  // https://wiki.nesdev.org/w/index.php?title=Cycle_counting
  totalCyclesPassed++;
  cyclesPassedThisInstruction++;
}

uint8_t R6502::getCyclesPassedThisInstruction() {
  return cyclesPassedThisInstruction;
}

uint8_t R6502::getExtraCyclesPassedThisInstruction() {
  return extraCyclesPassedThisInstruction;
}

void R6502::doRelBranch() {
  prepExtraCycle();
  doPossibleExtraCycle(); // default cycle....
  absAddr = pc + (int8_t) relAddr;
  if (absAddr & 0xFF00 != absAddr & 0xFF00) {
    prepExtraCycle();
    doPossibleExtraCycle(); // branch on different page, so extra cycle
  }

  setPC(absAddr);
}

void R6502::prepExtraCycle() {
  extraCyclePrepped = 0x01;
}


void R6502::doPossibleExtraCycle() {
  if (extraCyclePrepped) {
    doCycle();
    extraCyclesPassedThisInstruction++;
  }
  extraCyclePrepped = 0x00;
}

void R6502::clock() { }

void R6502::powerOn() {
  // Initialize power on state
  // Useful Variables
  absAddr = 0x0000;
  relAddr = 0x0000;
  operand = 0x00;
  tmp = 0x0000;

  accumulator = 0x00;
  x = 0x00;
  y = 0x00;

  P = 0x34; // 00110100 - https://www.nesdev.org/wiki/CPU_power_up_state#At_power-up

  RES();
}

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
  setFlags(I | Z);
  // And finally, the internal memory was unchanged

  // "...loads the program counter from the memory vector locations FFFC and FFFD..."
  // (Page 2 under RESET (RES)) http://archive.6502.org/datasheets/rockwell_r650x_r651x.pdf
  setPC(((uint16_t) read(0xFFFC) << 8) | ((uint16_t) read(0xFFFD)));

  // Done!
}

void R6502::IRQ() {
  pushStack16(pc);
  pushStack(P & ~B);
  setFlags(I); // B flag is cleared when pushed.
  setPC((uint16_t) read(0xFFFE) | (uint16_t) read(0xFFFF) << 8); // lo byte, than hi. C order of evalutation. Left expression first (lo).
}

void R6502::NMI() {
  pushStack16(pc);
  pushStack(P & ~B);
  setFlags(I); // B flag is cleared when pushed.
  setPC((uint16_t) read(0xFFFA) | (uint16_t) read(0xFFFB) << 8); // lo byte, than hi. C order of evalutation. Left expression first (lo).
}

uint8_t R6502::read(uint16_t addr) {
  doCycle();
  return memory->read(addr); 
}

uint8_t R6502::readPC() {
  uint8_t byte = read(pc);
  incPC();
  return byte; 
}

uint16_t R6502::read16(uint16_t addr) {
  return ((uint16_t) (read(addr + 1) << 8)) | read(addr); 
}

uint16_t R6502::readPC16() {
  uint16_t lo = (uint16_t) readPC();
  uint16_t hi = (uint16_t) readPC();

  return (hi << 8) | lo;
}

void R6502::write(uint16_t addr, uint8_t data) {
  doCycle();
  memory->write(addr, data);
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

uint8_t R6502::pullStackChain() {
  incSP();
  doCycle();
  return memory->read(0x0100 + sp);
}

uint16_t R6502::pullStackChain16() {
  uint16_t lo = (uint16_t) pullStackChain();
  uint16_t hi = (uint16_t) pullStackChain();
  return (hi << 8) | lo;
}

void R6502::endPullStackChain() {
  doCycle();
}

void R6502::pushStack(uint8_t byte) {
  write(0x0100 + sp, byte);
  decSP();
}

void R6502::pushStack16(uint16_t dbyte) {
  pushStack(dbyte >> 8); // Store higher order bits first
  pushStack(dbyte & 0x00FF); // Than lower.
  // its cause of the way stacks work. we want to fetch lo off the stack first.
}


// -------------
// Flag utils
// -------------

uint8_t R6502::isZero(uint8_t byte) {
  return byte ? 0x0 : Z;
}

uint8_t R6502::isZero(uint16_t doubleByte) {
  return doubleByte ? 0x0 : Z;
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

uint8_t R6502::getFlag(FLAGS flag) {
  return flag & P ? 1 : 0;
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
// Intructions utils.
// -----

uint8_t R6502::fetchOperand() {
  if (currentInstruction.addressMode != ACCUMULATOR) operand = read(absAddr);
  return operand;
}



// -----
// "Emulation hooking utils"
// -----

void R6502::onRegisterUpdate() {
  // Logging...
  return;
}

// -----
// Addressing modes - http://archive.6502.org/datasheets/rockwell_r650x_r651x.pdf
// -----

void R6502::modeImmediate() {
  absAddr = pc;
  incPC();
}  

void R6502::modeAbsolute() {
  if (currentInstruction.operation != JSR) {
    absAddr = readPC16();
  }
}

void R6502::modeAbsoluteX() {
  absAddr = readPC16();
  uint8_t hi = absAddr >> 8;
  absAddr += x;
 
  // Extra cycle is needed if page boundary crossed
  if (absAddr >> 8 != hi) prepExtraCycle();
}

void R6502::modeAbsoluteY() {
  absAddr = readPC16();
  uint8_t hi = absAddr >> 8;
  absAddr += y;
 
  // Extra cycle is needed if page boundary crossed
  if (absAddr >> 8 != hi) prepExtraCycle();
}

void R6502::modeImplied() {
  read(pc); // Read byte and throw it away <- https://www.nesdev.org/6502_cpu.txt
  operand = accumulator;
}

void R6502::modeAccumulator() {
  modeImplied();
}

void R6502::modeZeroPage() {
  absAddr = readPC();
}

void R6502::modeZeroPageX() {
  absAddr = read(readPC()) + x;
  absAddr &= 0x00FF; // no paging past the zero page may occur
}

void R6502::modeZeroPageY() {
  absAddr = read(readPC()) + y;
  absAddr &= 0x00FF; // no paging past the zero page may occur
}

void R6502::modeRelative() {
  relAddr = readPC();
  // if negative (MSB of lo byte == 1), set hi byte to FF since relAddr is 2 bytes, not 1 as read. This will keep the relative address negative when converted to 2 byte form.
  if (isNegative(relAddr)) {
    relAddr |= 0xFF00;
  }
}

void R6502::modeIndirectX() {
  uint16_t baseAddr = readPC();
  uint16_t loAddr = (read(baseAddr) + x) & 0x00FF;
  absAddr = read16(loAddr);
}

void R6502::modeIndirectY() {
  uint16_t baseAddr = readPC();
  absAddr = read16(baseAddr & 0x00FF);
  uint8_t hi = absAddr >> 8;
  absAddr += y;

  if (absAddr >> 8 != hi) {
    prepExtraCycle();
  }
}

void R6502::modeIndirect() {

  /*
    * Things start to look weird here in order to simulate a bug in the CPU.
    * From hnesdev.icequake.net/6502bugs.txt:
    * "An indirect JMP (xxFF) will fail because the MSB will be fetched from
    * address xx00 instead of page xx+1."
    * DO NOT simplify this. Need to make the bug clear and show details.
    */

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



void R6502::opADC() {
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

void R6502::opAND() {
  // A AND M -> A
  // Flags changed: Z N
  
  fetchOperand();
  setAccumulator(accumulator & operand);

  setFlags(Z | N, isZero(accumulator) | isNegative(accumulator));

  doPossibleExtraCycle();
}

void R6502::opASL() {
  // C <- [76543210] <- 0
  // Flags changed: C Z N
  
  fetchOperand();

  if (currentInstruction.addressMode == ABSOLUTEX
      || currentInstruction.addressMode == ABSOLUTEY) read(absAddr);
  if (currentInstruction.addressMode != ACCUMULATOR) write(absAddr, operand);
  
  tmp = (uint16_t) operand << 1;
  //doCycle(); // Internal operation cycle (3a) <- https://the-dreams.de/aay64.txt

  setFlags(C | Z | N, isCarry(tmp) | isZero(tmp) | isNegative(tmp));

  if (currentInstruction.addressMode == ACCUMULATOR) setAccumulator(tmp & 0x00FF);
  else write(absAddr, tmp & 0x00FF);
}

void R6502::opBCC() {
  // branch on C = 0
  // Flags changed: 

  if (getFlag(C) == 0) doRelBranch();
}

void R6502::opBCS() {
  // branch on C = 1
  // Flags changed: 

  if (getFlag(C) != 0) doRelBranch();
}

void R6502::opBEQ() {
  // branch on Z = 1
  // Flags changed: 

  if (getFlag(Z) != 0) {
    doRelBranch();
  }
}

void R6502::opBIT() {
  // A AND M, M7 -> N, M6 -> V
  // Flags changed: Z N V
  
  fetchOperand();

  tmp = (accumulator & operand);
  
  setFlags(Z | N | V, isZero(tmp) | isNegative(operand) | (operand & (1 << 6)));
}

void R6502::opBMI() {
  // branch on N = 1
  // Flags changed: 

  if (getFlag(N) != 0) doRelBranch();
}

void R6502::opBNE() {
  // branch on Z = 0
  // Flags changed: 

  if (getFlag(Z) == 0) doRelBranch();
}

void R6502::opBPL() {
  // branch on N = 0
  // Flags changed: 
  
  if (getFlag(N) == 0) doRelBranch();
}

void R6502::opBRK() {
  // interrupt, push PC+2, push SR
  // Flags Changed: I
  
  // https://www.pagetable.com/?p=410
  // http://archive.6502.org/datasheets/synertek_programming_manual.pdf - p. 131

  pushStack16(pc);
  // https://www.masswerk.at/6502/6502_instruction_set.html#BRK
  setFlags(I | B);
  pushStack(P); // Store status reg.

  // https://wiki.nesdev.org/w/index.php?title=CPU_interrupts#Interrupt_hijacking
  // (Interrupt Request (IRQ)) http://archive.6502.org/datasheets/rockwell_r650x_r651x.pdf
  // "$FFFE-$FFFF = IRQ/BRK vector" https://wiki.nesdev.org/w/index.php?title=CPU_memory_map
  setPC((uint16_t) read(0xFFFE) | (uint16_t) read(0xFFFF) << 8); // lo byte, than hi. C order of evalutation. Left expression first (lo).
}

void R6502::opBVC() {
  // branch on V = 0
  // Flags changed: 

  if (getFlag(V) == 0) doRelBranch();
}

void R6502::opBVS() {
  // branch on V = 1
  // Flags changed: 
  
  if (getFlag(V) != 0) doRelBranch();
}

void R6502::opCLC() {
  // 0 -> C
  // Flags changed: C
  setFlags(C, 0);
}

void R6502::opCLD() {
  // 0 -> D
  // Flags changed: D
  setFlags(D, 0);
}

void R6502::opCLI() {
  // 0 -> I
  // Flags changed: I
  setFlags(I, 0);
}

void R6502::opCLV() {
  // 0 -> V
  // Flags changed: V
  setFlags(V, 0);
}

void R6502::opCMP() {
  // A - M
  // Flags changed: N Z C
  fetchOperand();

  tmp = ((uint16_t) accumulator - (uint16_t) operand) & 0x00FF;

  setFlags(Z | N | C, isZero(tmp) | isNegative(tmp) | (accumulator >= operand ? C : 0x0));
}

void R6502::opCPX() {
  // X - M
  // Flags changed: N Z C
  fetchOperand();

  tmp = ((uint16_t) x - (uint16_t) operand) & 0x00FF;

  setFlags(Z | N | C, isZero(tmp) | isNegative(tmp) | x >= operand ? C : 0x0);
}

void R6502::opCPY() {
  // Y - M
  // Flags changed: N Z C
  fetchOperand();

  tmp = ((uint16_t) y - (uint16_t) operand) & 0x00FF;

  setFlags(Z | N | C, isZero(tmp) | isNegative(tmp) | y >= operand ? C : 0x0);
}

void R6502::opDEC() {
  // M - 1 -> M
  // Flags changed: Z N
  
  fetchOperand();

  if (currentInstruction.addressMode == ABSOLUTEX)
    //doPossibleExtraCycle();
    fetchOperand();

  write(absAddr, operand);

  tmp = ((uint16_t) operand - 1) & 0x00FF;

  write(absAddr, tmp);
  
  setFlags(Z | N, isZero(tmp) | isNegative(tmp));
}

void R6502::opDEX() {
  // X - 1 -> X
  // Flags changed: Z N

  decX();
  setFlags(Z | N, isZero(x) | isNegative(x));
}

void R6502::opDEY() {
  // Y - 1 -> Y
  // Flags changed: Z N

  decY();
  setFlags(Z | N, isZero(y) | isNegative(y));
}

void R6502::opEOR() {
  // A EOR M -> A
  // Flags changed: Z N

  fetchOperand();

  setAccumulator(accumulator ^ operand);
  setFlags(Z | N, isZero(accumulator) | isNegative(accumulator));

  doPossibleExtraCycle();
}

void R6502::opINC() {
  // M + 1 -> M
  // Flags changed: Z N
  
  fetchOperand();

  if (currentInstruction.addressMode == ABSOLUTEX)
    fetchOperand();

  write(absAddr, operand);

  tmp = ((uint16_t) operand + 1) & 0x00FF;

  write(absAddr, tmp);
  setFlags(Z | N, isZero(tmp) | isNegative(tmp));
}

void R6502::opINX() {
  // X - 1 -> X
  // Flags changed: Z N

  incX();
  setFlags(Z | N, isZero(x) | isNegative(x));
}

void R6502::opINY() {
  // Y + 1 -> Y
  // Flags changed: Z N

  incY();
  setFlags(Z | N, isZero(y) | isNegative(y));
}

void R6502::opJMP() {
  // (PC+1) -> PCL
  // (PC+2) -> PCH
  // Flags changed:
  setPC(absAddr);
}

void R6502::opJSR() {
  // push (PC+2),
  // (PC+1) -> PCL
  // (PC+2) -> PCH
  // Flags changed:

  absAddr = readPC();
  read(sp); // Internal Operation <- https://the-dreams.de/aay64.txt (LOL?????? No way they designed a wasted cpu cycle... come back if you have errors)
  pushStack16(pc);
  absAddr = absAddr | (((uint16_t) readPC()) << 8);
  setPC(absAddr);
}

void R6502::opLDA() {
  // M -> A
  // Flags changed: Z N

  fetchOperand();
  setAccumulator(operand);
  setFlags(Z | N, isZero(accumulator) | isNegative(accumulator));
  doPossibleExtraCycle();
}

void R6502::opLDX() {
  // M -> X
  // Flags changed: Z N

  fetchOperand();
  setX(operand);
  setFlags(Z | N, isZero(x) | isNegative(x));
  doPossibleExtraCycle();
}

void R6502::opLDY() {
  // M -> Y
  // Flags changed: Z N

  fetchOperand();
  setY(operand);
  setFlags(Z | N, isZero(y) | isNegative(y));
  doPossibleExtraCycle();
}

void R6502::opLSR() {
  // 0 -> [76543210] -> C
  // Flags changed: Z N C
  
  fetchOperand();
  if (currentInstruction.addressMode == ABSOLUTEX
    || currentInstruction.addressMode == ABSOLUTEY) fetchOperand(); 
  
  if (currentInstruction.addressMode != ACCUMULATOR) write(absAddr, operand);

  tmp = (uint16_t) operand >> 1;

  setFlags(C | Z | N, isZero(tmp) | isCarry(tmp));

  if (currentInstruction.addressMode == ACCUMULATOR) setAccumulator(tmp & 0x00FF);
  else write(absAddr, tmp & 0x00FF);
}

void R6502::opNOP() {
  // No operation.
  // Flags changed: 
  return;
}

void R6502::opORA() {
  // A OR M -> A
  // Flags changed: Z N
  
  fetchOperand();

  setAccumulator(accumulator | operand);
  setFlags(Z | N, isZero(accumulator) | isNegative(accumulator));

  doPossibleExtraCycle();
}

void R6502::opPHA() {
  // push A
  // Flags changed:
  
  pushStack(accumulator);
}

void R6502::opPHP() {
  // push P
  // Flags changed:
  
  pushStack(P);
}

void R6502::opPLA() {
  // pull A
  // Flags changed: Z N

  setAccumulator(pullStackChain());
  endPullStackChain();
  setFlags(Z | N, isZero(accumulator) | isNegative(accumulator));
}

void R6502::opPLP() {
  // pull P
  // Flags changed: FROM STACK
  setP(pullStackChain());
  endPullStackChain();
}

void R6502::opROL() {
  // C <- [76543210] <- C
  // Flags Changed: C Z N
  
  fetchOperand();
  if (currentInstruction.addressMode == ABSOLUTEX
    || currentInstruction.addressMode == ABSOLUTEY) fetchOperand();

  if (currentInstruction.addressMode != ACCUMULATOR) write(absAddr, operand);

  tmp = ((uint16_t) (operand << 1) | (uint16_t) (operand >> 7)) & 0x00FF;

  setFlags(C | Z | N, isZero(tmp) | isNegative(tmp) | operand & 0x80 ? C : 0x0);
  
  if (currentInstruction.addressMode == ACCUMULATOR) setAccumulator(tmp);
  else write(absAddr, tmp);
}

void R6502::opROR() {
  // C -> [76543210] -> C
  // Flags Changed: C Z N
  
  fetchOperand();
  if (currentInstruction.addressMode == ABSOLUTEX
    || currentInstruction.addressMode == ABSOLUTEY) fetchOperand();

  if (currentInstruction.addressMode != ACCUMULATOR) write(absAddr, operand);

  tmp = ((uint16_t) (operand >> 1) | (uint16_t) (operand << 7)) & 0x00FF;

  setFlags(C | Z | N, isZero(tmp) | isNegative(tmp) | operand & 0x01 ? C : 0x0);
  
  if (currentInstruction.addressMode == ACCUMULATOR) setAccumulator(tmp);
  else write(absAddr, tmp);
}

void R6502::opRTI() {
  // pull P, pull PC
  // Flags changed: FROM STACK
  // "The status register is pulled with the break flag
  // ...and bit 5 ignored. Then PC is pulled from the stack."
  
  setP(setBitsOfByte(U | B, P, pullStackChain()));
  setPC(pullStackChain16());
  endPullStackChain();
}

void R6502::opRTS() {
  // pull PC, PC+1 -> PC

  
  setPC(pullStackChain16());
  endPullStackChain();
  incPC();
  doCycle();
}

void R6502::opSBC() {
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

void R6502::opSEC() {
  // 1 -> C
  // Flags changed: C

  setFlags(C);
}

void R6502::opSED() {
  // 1 -> D
  // Flags changed: D

  setFlags(D);
}

void R6502::opSEI() {
  // 1 -> I
  // Flags changed: I

  setFlags(I);
}

void R6502::opSTA() {
  // A -> M
  // Flags changed: 

  if (
    currentInstruction.addressMode == INDIRECTY ||
    currentInstruction.addressMode == ABSOLUTEY ||
    currentInstruction.addressMode == ABSOLUTEX
  )
    fetchOperand(); // Read from effective address...? <- https://www.nesdev.org/6502_cpu.txt

  write(absAddr, accumulator);
}

void R6502::opSTX() {
  // X -> M
  // Flags changed: 

  write(absAddr, x);
}

void R6502::opSTY() {
  // Y -> M
  // Flags changed: 

  write(absAddr, y);
}

void R6502::opTAX() {
  // A -> X
  // Flags changed: Z N

  setX(accumulator);
  setFlags(Z | N, isZero(x) | isNegative(x));
}

void R6502::opTAY() {
  // A -> Y
  // Flags changed: Z N

  setY(accumulator);
  setFlags(Z | N, isZero(y) | isNegative(y));
}

void R6502::opTSX() {
  // SP -> X
  // Flags changed: Z N

  setX(sp);
  setFlags(Z | N, isZero(x) | isNegative(x));
}

void R6502::opTXA() {
  // X -> A
  // Flags changed: Z N

  setAccumulator(x);
  setFlags(Z | N, isZero(accumulator) | isNegative(accumulator));
}

void R6502::opTXS() {
  // X -> SP
  // Flags changed: Z N

  setSP(x);
  setFlags(Z | N, isZero(sp) | isNegative(sp));
}

void R6502::opTYA() {
  // Y -> A
  // Flags changed: Z N

  setAccumulator(y);
  setFlags(Z | N, isZero(accumulator) | isNegative(accumulator));
}









void R6502::modeIllegal()
{
  
}

void R6502::opIllegal() { // Does nothing, illegal instruction
  return;
}




