#include "NESIncludes.h"
#include <iostream>
#include <iomanip>

using namespace util::byte; // for readability...

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

const R6502::ModeFunc R6502::modeFuncs[14] = {
  &R6502::modeIllegal,
  &R6502::modeImmediate,
  &R6502::modeAbsolute, &R6502::modeAbsoluteX, &R6502::modeAbsoluteY,
  &R6502::modeImplied, &R6502::modeAccumulator,
  &R6502::modeZeroPage, &R6502::modeZeroPageX, &R6502::modeZeroPageY,
  &R6502::modeRelative,
  &R6502::modeIndirect, &R6502::modeIndirectX, &R6502::modeIndirectY
};

const R6502::OpFunc R6502::opFuncs[57] = {
  &R6502::opIllegal,
  &R6502::opADC, &R6502::opAND, &R6502::opASL, &R6502::opBCC, &R6502::opBCS, &R6502::opBEQ, &R6502::opBIT, &R6502::opBMI,
  &R6502::opBNE, &R6502::opBPL, &R6502::opBRK, &R6502::opBVC, &R6502::opBVS, &R6502::opCLC, &R6502::opCLD, &R6502::opCLI,
  &R6502::opCLV, &R6502::opCMP, &R6502::opCPX, &R6502::opCPY, &R6502::opDEC, &R6502::opDEX, &R6502::opDEY, &R6502::opEOR,
  &R6502::opINC, &R6502::opINX, &R6502::opINY, &R6502::opJMP, &R6502::opJSR, &R6502::opLDA, &R6502::opLDX, &R6502::opLDY,
  &R6502::opLSR, &R6502::opNOP, &R6502::opORA, &R6502::opPHA, &R6502::opPHP, &R6502::opPLA, &R6502::opPLP, &R6502::opROL,
  &R6502::opROR, &R6502::opRTI, &R6502::opRTS, &R6502::opSBC, &R6502::opSEC, &R6502::opSED, &R6502::opSEI, &R6502::opSTA,
  &R6502::opSTX, &R6502::opSTY, &R6502::opTAX, &R6502::opTAY, &R6502::opTSX, &R6502::opTXA, &R6502::opTXS, &R6502::opTYA
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

void R6502::doAddressMode(MODES mode) {
  (this->*modeFuncs[mode])();
}

void R6502::doOperation(OPS op, uint16_t fetchAddress) {
  (this->*opFuncs[op])(fetchOperand(fetchAddress));
}

void R6502::doInstruction(const Instruction& instruction) {
  currentInstruction = instruction;
  doAddressMode(currentInstruction.addressMode);
  doOperation(currentInstruction.operation, fetchAddress);
  opWrite();
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

void R6502::doRelBranch(uint8_t operand) {
  prepExtraCycle();
  doPossibleExtraCycle(); // default cycle....
  fetchAddress = pc + (int8_t) operand;
  if (hi16(fetchAddress - pc) != hi16(fetchAddress)) {
    prepExtraCycle();
    doPossibleExtraCycle(); // branch on different page, so extra cycle
  }

  setPC(fetchAddress);
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

void R6502::clock() {
  if (cyclesPassedThisInstruction == 0x00) {
    doNextInstruction();
  }
  cyclesPassedThisInstruction--;
}

void R6502::powerOn() {
  // Initialize power on state
  // Useful Variables
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
  setPC(hi16(read(0xFFFC)) | lo16(read(0xFFFD)));

  // Done!
}

void R6502::IRQ() {
  pushStack16(pc);
  pushStack(P & ~B);
  setFlags(I); // B flag is cleared when pushed.
  setPC(lo16(read(0xFFFE)) | hi16(read(0xFFFF))); // lo byte, than hi. C order of evalutation. Left expression first (lo). I AM BEING CAUTIOUS OF READ ORDER.
}

void R6502::NMI() {
  pushStack16(pc);
  pushStack(P & ~B);
  setFlags(I); // B flag is cleared when pushed.
  setPC(lo16(read(0xFFFA)) | hi16(read(0xFFFB))); // lo byte, than hi. C order of evalutation. Left expression first (lo). I AM BEING CAUTIOUS OF READ ORDER.
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
  //return dbyte(read(addr + 1), read(addr)); 
  return ((uint16_t) (read(addr + 1) << 8)) | read(addr); 
}

uint16_t R6502::readPC16() {
  uint8_t lo = readPC();
  uint8_t hi = readPC();

  return dbyte(hi, lo);
}

void R6502::write(uint16_t addr, uint8_t data) {
  doCycle();
  memory->write(addr, data);
}

void R6502::prepWrite(uint8_t byte) {
  switch (currentInstruction.addressMode) {
    case ACCUMULATOR:
      setAccumulator(byte);
      break;
    case IMPLIED:
      break;
    case RELATIVE:
      break;

    default:
      enableWrite = 0x01;
  }

  writeReg = byte;
}

void R6502::prepWrite(uint16_t dbyte) {
  prepWrite(lo(dbyte));
}

void R6502::opWrite() {
  if (enableWrite) {
    write(fetchAddress, writeReg);
    enableWrite = 0x00;
  }
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
  uint8_t lo = pullStackChain();
  uint8_t hi = pullStackChain();
  return dbyte(hi, lo);
}

void R6502::endPullStackChain() {
  doCycle();
}

void R6502::pushStack(uint8_t byte) {
  write(0x0100 + sp, byte);
  decSP();
}

void R6502::pushStack16(uint16_t dbyte) {
  pushStack(hi(dbyte)); // Store higher order bits first
  pushStack(lo(dbyte)); // Than lower.
  // its cause of the way stacks work. we want to fetch lo off the stack first.
}


// -------------
// Flag utils
// -------------

uint8_t R6502::isZero(uint8_t byte) {
  return getFlagByteAs(Z, util::byte::isZero(byte));
}

uint8_t R6502::isZero(uint16_t dbyte) {
  return getFlagByteAs(Z, util::byte::isZero(dbyte));
}

uint8_t R6502::isNegative(uint8_t byte) {
  return getFlagByteAs(N, util::byte::isNegative(byte));
}

uint8_t R6502::isNegative(uint16_t dbyte) {
  return getFlagByteAs(N, util::byte::isNegative(dbyte));
}

uint8_t R6502::isCarry(uint16_t dbyte) {
  return getFlagByteAs(C, util::byte::isCarry(dbyte));
}

uint8_t R6502::getFlagByteAs(FLAGS flag, uint8_t value) {
  return value ? flag : 0x00;
}

uint8_t R6502::getFlag(FLAGS flag) {
  return (flag & P) ? 1 : 0;
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

uint8_t R6502::fetchOperand(uint16_t fetchAddress) {
  switch (currentInstruction.addressMode) {
    case ACCUMULATOR:
      return accumulator;
    case IMPLIED:
      return accumulator;
    case RELATIVE:
      return lo(fetchAddress);

    default:
      return read(fetchAddress);
  }
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
  fetchAddress = pc;
  incPC();
}  

void R6502::modeAbsolute() {
  if (currentInstruction.operation != JSR) {
    fetchAddress = readPC16();
  }
}

void R6502::modeAbsoluteX() {
  fetchAddress = readPC16() + x;
 
  // Extra cycle is needed if page boundary crossed
  if (hi16(fetchAddress) != hi16(fetchAddress - x)) prepExtraCycle();
}

void R6502::modeAbsoluteY() {
  fetchAddress = readPC16() + y;
 
  // Extra cycle is needed if page boundary crossed
  if (hi(fetchAddress) != hi(fetchAddress - y)) prepExtraCycle();
}

void R6502::modeImplied() {
  read(pc); // Read byte and throw it away <- https://www.nesdev.org/6502_cpu.txt
  fetchAddress = pc;
}

void R6502::modeAccumulator() {
  modeImplied();
}

void R6502::modeZeroPage() {
  fetchAddress = readPC();
}

void R6502::modeZeroPageX() {
  fetchAddress = lo16(readPC() + x); // no paging past the zero page may occur
}

void R6502::modeZeroPageY() {
  fetchAddress = lo16(readPC() + y); // no paging past the zero page may occur
}

void R6502::modeRelative() {
  fetchAddress = dbyte(readPC());
  // if negative (MSB of lo byte == 1), set hi byte to FF since addresses are 2 bytes. This will keep the relative address negative when converted to dbyte form.
  if (isNegative(tmp)) {
    tmp |= 0xFF00;
  }
}

void R6502::modeIndirectX() {
  uint8_t baseAddr = readPC();
  fetchAddress = read16(lo16(baseAddr + x)); // zero page wrap around https://www.nesdev.org/obelisk-6502-guide/addressing.html
}

void R6502::modeIndirectY() {
  uint16_t baseAddr = readPC();
  fetchAddress = read16(lo16(baseAddr));
  fetchAddress = fetchAddress + y;

  if (hi16(fetchAddress - y) != hi16(fetchAddress)) {
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

  uint16_t loAddr = dbyte(pointerHi, pointerLo);
  // hiAddr is intentionally bugged. pointerLo + 1 can overflow.
  uint16_t hiAddr = dbyte(pointerHi, pointerLo + 1);

  uint8_t hi = read(hiAddr);
  uint8_t lo = read(loAddr);

  fetchAddress = dbyte(hi, lo);
}





// -----
// Instructions - https://www.masswerk.at/6502/6502_instruction_set.html
// -----



void R6502::opADC(uint8_t operand) {
  // A + M + C -> A, C
  // Flags changed: C Z N V

  tmp = dbyte(accumulator) + dbyte(operand) + dbyte(getFlag(C));

  // Tempted to do an adder impl.
  
  // Overflow happens when both operands have the same sign but the result is a different sign.
  // 1. XNOR the 2 operands, the MSB in the result is whether or not the signs are the same.
  // 2. check if the sign of the result differs from the sign of either operand (XOR both with the result)
  // 3. if both operations result in 1, then overflow has occured.
  // Why? because "result" is the same in both operations. If the operations result in the same sign, then it is implied that accumulator and operand have the same sign.
  uint8_t overflowBit = (accumulator ^ lo(tmp)) & (operand ^ lo(tmp));

  setFlags(
    C | Z | N | V,
    isCarry(tmp) |
    isZero(lo(tmp)) |
    isNegative(tmp) |
    getFlagByteAs(V, isNegative(overflowBit))
  );

  setAccumulator(lo(tmp));

  doPossibleExtraCycle();
}

void R6502::opAND(uint8_t operand) {
  // A AND M -> A
  // Flags changed: Z N
  setAccumulator(accumulator & operand);

  setFlags(
    Z | N,
    isZero(accumulator) |
    isNegative(accumulator)
  );

  doPossibleExtraCycle();
}

void R6502::opASL(uint8_t operand) {
  // C <- [76543210] <- 0
  // Flags changed: C Z N

  if (currentInstruction.addressMode == ABSOLUTEX
      || currentInstruction.addressMode == ABSOLUTEY)
      //read(fetchAddress);
      doCycle(); // redundant cycle?????

  if (currentInstruction.addressMode != ACCUMULATOR)
    //write(fetchAddress, operand); // for redundanct write on hardware
    doCycle();
  
  tmp = dbyte(operand) << 1;
  //doCycle(); // Internal operation cycle (3a) <- https://the-dreams.de/aay64.txt

  setFlags(
    C | Z | N,
    isCarry(tmp) |
    isZero(lo(tmp)) |
    isNegative(tmp)
  );

  return prepWrite(tmp);
}

void R6502::opBCC(uint8_t operand) {
  // branch on C = 0
  // Flags changed: 

  if (getFlag(C) == 0) doRelBranch(operand);
}

void R6502::opBCS(uint8_t operand) {
  // branch on C = 1
  // Flags changed: 

  if (getFlag(C) != 0) doRelBranch(operand);
}

void R6502::opBEQ(uint8_t operand) {
  // branch on Z = 1
  // Flags changed: 

  if (getFlag(Z) != 0) doRelBranch(operand);
}

void R6502::opBIT(uint8_t operand) {
  // A AND M, M7 -> N, M6 -> V
  // Flags changed: Z N V

  tmp = (accumulator & operand);
  
  setFlags(
    Z | N | V,
    isZero(tmp) |
    isNegative(operand) |
    getFlagByteAs(V, operand & (1 << 6))
  );
}

void R6502::opBMI(uint8_t operand) {
  // branch on N = 1
  // Flags changed: 

  if (getFlag(N) != 0) doRelBranch(operand);
}

void R6502::opBNE(uint8_t operand) {
  // branch on Z = 0
  // Flags changed: 

  if (getFlag(Z) == 0) doRelBranch(operand);
}

void R6502::opBPL(uint8_t operand) {
  // branch on N = 0
  // Flags changed: 
  
  if (getFlag(N) == 0) doRelBranch(operand);
}

void R6502::opBRK(uint8_t operand) {
  // interrupt, push PC+2, push SR
  // Flags Changed: I
  
  // https://www.pagetable.com/?p=410
  // http://archive.6502.org/datasheets/synertek_programming_manual.pdf - p. 131

  pushStack16(pc+1);
  // https://www.masswerk.at/6502/6502_instruction_set.html#BRK
  setFlags(B);
  pushStack(P); // Store status reg.

  // PLEASE NOT ON REAL HARDWARE, THE INSTRUCTION ITSELF DOES NOT SET THE I FLAG!!! PLEASE VERIFY THIS LATER! IT IS IMPLICITLY SET WHEN FORCING AN INTERRUPT!
  setFlags(I);


  // https://wiki.nesdev.org/w/index.php?title=CPU_interrupts#Interrupt_hijacking
  // (Interrupt Request (IRQ)) http://archive.6502.org/datasheets/rockwell_r650x_r651x.pdf
  // "$FFFE-$FFFF = IRQ/BRK vector" https://wiki.nesdev.org/w/index.php?title=CPU_memory_map
  setPC(((uint16_t) read(0xFFFE)) | ((uint16_t) read(0xFFFF) << 8)); // lo byte, than hi. C order of evalutation. Left expression first (lo).
}

void R6502::opBVC(uint8_t operand) {
  // branch on V = 0
  // Flags changed: 

  if (getFlag(V) == 0) doRelBranch(operand);
}

void R6502::opBVS(uint8_t operand) {
  // branch on V = 1
  // Flags changed: 
  
  if (getFlag(V) != 0) doRelBranch(operand);
}

void R6502::opCLC(uint8_t operand) {
  // 0 -> C
  // Flags changed: C
  setFlags(C, 0);
}

void R6502::opCLD(uint8_t operand) {
  // 0 -> D
  // Flags changed: D
  setFlags(D, 0);
}

void R6502::opCLI(uint8_t operand) {
  // 0 -> I
  // Flags changed: I
  setFlags(I, 0);
}

void R6502::opCLV(uint8_t operand) {
  // 0 -> V
  // Flags changed: V
  setFlags(V, 0);
}

void R6502::opCMP(uint8_t operand) {
  // A - M
  // Flags changed: N Z C
  tmp = lo16(dbyte(accumulator) - dbyte(operand));

  setFlags(
    Z | N | C,
    isZero(tmp) |
    isNegative(tmp) |
    getFlagByteAs(C, accumulator >= operand)
  );
}

void R6502::opCPX(uint8_t operand) {
  // X - M
  // Flags changed: N Z C
  tmp = lo16(dbyte(x) - dbyte(operand));

  setFlags(
    Z | N | C,
    isZero(tmp) |
    isNegative(tmp) |
    getFlagByteAs(C, x >= operand)
  );
}

void R6502::opCPY(uint8_t operand) {
  // Y - M
  // Flags changed: N Z C
  tmp = lo16(dbyte(y) - dbyte(operand));

  setFlags(
    Z | N | C,
    isZero(tmp) |
    isNegative(tmp) |
    getFlagByteAs(C, y >= operand)
  );
}

void R6502::opDEC(uint8_t operand) {
  // M - 1 -> M
  // Flags changed: Z N
  if (currentInstruction.addressMode == ABSOLUTEX) // What is this?????? check cycle accuracy later
    //fetchOperand(); ????????? check when fixing cycle acc
    doCycle();

  //write(fetchAddress, operand);
  doCycle(); // For redundant write on hardware.

  tmp = dbyte(operand - 1);

  setFlags(
    Z | N,
    isZero(tmp) |
    isNegative(tmp)
  );

  prepWrite(tmp);
}

void R6502::opDEX(uint8_t operand) {
  // X - 1 -> X
  // Flags changed: Z N

  decX();
  setFlags(
    Z | N,
    isZero(x) |
    isNegative(x)
  );
}

void R6502::opDEY(uint8_t operand) {
  // Y - 1 -> Y
  // Flags changed: Z N

  decY();
  setFlags(
    Z | N,
    isZero(y) |
    isNegative(y)
  );
}

void R6502::opEOR(uint8_t operand) {
  // A EOR M -> A
  // Flags changed: Z N

  setAccumulator(accumulator ^ operand);
  setFlags(
    Z | N,
    isZero(accumulator) |
    isNegative(accumulator)
  );

  doPossibleExtraCycle();
}

void R6502::opINC(uint8_t operand) {
  // M + 1 -> M
  // Flags changed: Z N
  if (currentInstruction.addressMode == ABSOLUTEX)
    //fetchOperand(); ????????? check when fixing cycle acc
    doCycle(); // For redundant write on hardware.

  //write(fetchAddress, operand);
  doCycle(); // For redundant write on hardware.

  tmp = dbyte(operand + 1);

  setFlags(
    Z | N,
    isZero(tmp) |
    isNegative(tmp)
  );

  prepWrite(tmp);
}

void R6502::opINX(uint8_t operand) {
  // X - 1 -> X
  // Flags changed: Z N

  incX();
  setFlags(
    Z | N,
    isZero(x) |
    isNegative(x)
  );
}

void R6502::opINY(uint8_t operand) {
  // Y + 1 -> Y
  // Flags changed: Z N

  incY();
  setFlags(
    Z | N,
    isZero(y) |
    isNegative(y)
  );
}

void R6502::opJMP(uint8_t operand) {
  // (PC+1) -> PCL
  // (PC+2) -> PCH
  // Flags changed:
  setPC(fetchAddress);
}

void R6502::opJSR(uint8_t operand) {
  // push (PC+2),
  // (PC+1) -> PCL
  // (PC+2) -> PCH
  // Flags changed:

  tmp = dbyte(readPC());
  read(sp); // Internal Operation <- https://the-dreams.de/aay64.txt (LOL?????? No way they designed a wasted cpu cycle... come back if you have errors)
  pushStack16(pc);
  tmp = dbyte(readPC(), lo(tmp)); // hi of absolute address is guaranteed to be 0x00
  setPC(tmp);
}

void R6502::opLDA(uint8_t operand) {
  // M -> A
  // Flags changed: Z N
  setAccumulator(operand);
  setFlags(
    Z | N,
    isZero(accumulator) |
    isNegative(accumulator)
  );

  doPossibleExtraCycle();
}

void R6502::opLDX(uint8_t operand) {
  // M -> X
  // Flags changed: Z N
  setX(operand);
  setFlags(
    Z | N,
    isZero(x) |
    isNegative(x)
  );

  doPossibleExtraCycle();
}

void R6502::opLDY(uint8_t operand) {
  // M -> Y
  // Flags changed: Z N
  setY(operand);
  setFlags(
    Z | N,
    isZero(y) |
    isNegative(y)
  );

  doPossibleExtraCycle();
}

void R6502::opLSR(uint8_t operand) {
  // 0 -> [76543210] -> C
  // Flags changed: Z N C
  if (currentInstruction.addressMode == ABSOLUTEX
    || currentInstruction.addressMode == ABSOLUTEY)
    //fetchOperand(); 
    doCycle(); // ????????? check when fixing cycle acc
  
  if (currentInstruction.addressMode != ACCUMULATOR)
    //write(fetchAddress, operand);
    doCycle(); // for redundant write on hardware

  tmp = dbyte(operand >> 1);

  setFlags(
    C | Z | N,
    getFlagByteAs(C, operand & 0x01) |
    isZero(tmp) |
    0x00
  );

  prepWrite(tmp);
}

void R6502::opNOP(uint8_t operand) {
  // No operation.
  // Flags changed: 
  return;
}

void R6502::opORA(uint8_t operand) {
  // A OR M -> A
  // Flags changed: Z N
  setAccumulator(accumulator | operand);
  setFlags(
    Z | N,
    isZero(accumulator) |
    isNegative(accumulator)
  );

  doPossibleExtraCycle();
}

void R6502::opPHA(uint8_t operand) {
  // push A
  // Flags changed:
  pushStack(accumulator);
}

void R6502::opPHP(uint8_t operand) {
  // push P
  // Flags changed:
  pushStack(P | B | U);
}

void R6502::opPLA(uint8_t operand) {
  // pull A
  // Flags changed: Z N
  setAccumulator(pullStackChain());
  endPullStackChain();
  setFlags(
    Z | N,
    isZero(accumulator) |
    isNegative(accumulator)
  );
}

void R6502::opPLP(uint8_t operand) {
  // pull P
  // Flags changed: FROM STACK
  setP(pullStackChain());
  endPullStackChain();
}

void R6502::opROL(uint8_t operand) {
  // C <- [76543210] <- C
  // Flags Changed: C Z N
  if (currentInstruction.addressMode == ABSOLUTEX
    || currentInstruction.addressMode == ABSOLUTEY)
    //fetchOperand(); ????????? check when fixing cycle acc
    doCycle();

  if (currentInstruction.addressMode != ACCUMULATOR)
    //write(fetchAddress, operand); // for redundant write on hardware
    doCycle();


  
  tmp = dbyte((operand << 1) | getFlag(C));
  setFlags(
    C | Z | N,
    getFlagByteAs(C, operand & 0x80) |
    isZero(tmp) |
    isNegative(tmp)
  );

  prepWrite(tmp);
}

void R6502::opROR(uint8_t operand) {
  // C -> [76543210] -> C
  // Flags Changed: C Z N
  if (currentInstruction.addressMode == ABSOLUTEX
    || currentInstruction.addressMode == ABSOLUTEY)
    //fetchOperand(); ????????? check when fixing cycle acc
    doCycle();

  if (currentInstruction.addressMode != ACCUMULATOR)
    //write(fetchAddress, operand); // for redundant write on hardware
    doCycle();


  
  tmp = dbyte((operand >> 1) | (getFlag(C) << 7));
  setFlags(
    C | Z | N,
    isZero(tmp) |
    isNegative(tmp) |
    getFlagByteAs(C, operand & 0x01)
  );

  prepWrite(tmp);
}

void R6502::opRTI(uint8_t operand) {
  // pull P, pull PC
  // Flags changed: FROM STACK
  // "The status register is pulled with the break flag
  // ...and bit 5 ignored. Then PC is pulled from the stack."
  
  setP(setBitsOfByte(U | B, P, pullStackChain()));
  setPC(pullStackChain16());
  endPullStackChain();
}

void R6502::opRTS(uint8_t operand) {
  // pull PC, PC+1 -> PC

  
  setPC(pullStackChain16());
  endPullStackChain();
  incPC();
  doCycle();
}

void R6502::opSBC(uint8_t operand) {
  // A - M - (1 - C) -> A
  // C is a single bit. 1 - C is the inverse of C (C(bar)).
  // A - M - (1 - C) == A + (-M - (1 - C)) == A + (-M - 1 + C)
  // The -M and -1 Cancel because 2's complement
  // If M = 010, then -M = 110
  // -M - 1 = 101
  // M is simply inverted and we can remove the -1
  // A + (~M) + C
  // Flags changed: V C Z N

  // Same as addition, but invert memory
  tmp = dbyte(accumulator) + dbyte(~operand) + dbyte(getFlag(C));

  uint8_t overflowBit = (accumulator ^ lo(tmp)) & ((~operand) ^ lo(tmp));
  setFlags(
    V | C | Z | N,
    getFlagByteAs(V, isNegative(overflowBit)) |
    isCarry(tmp) |
    isZero(lo(tmp)) |
    isNegative(tmp)
  );

  setAccumulator(lo(tmp));

  doPossibleExtraCycle();
}

void R6502::opSEC(uint8_t operand) {
  // 1 -> C
  // Flags changed: C

  setFlags(C);
}

void R6502::opSED(uint8_t operand) {
  // 1 -> D
  // Flags changed: D

  setFlags(D);
}

void R6502::opSEI(uint8_t operand) {
  // 1 -> I
  // Flags changed: I

  setFlags(I);
}

void R6502::opSTA(uint8_t operand) {
  // A -> M
  // Flags changed: 

  if (
    currentInstruction.addressMode == INDIRECTY ||
    currentInstruction.addressMode == ABSOLUTEY ||
    currentInstruction.addressMode == ABSOLUTEX
  )
    //fetchOperand(); // Read from effective address...? <- https://www.nesdev.org/6502_cpu.txt
    doCycle(); // ????????? check when fixing cycle acc

  prepWrite(accumulator);
}

void R6502::opSTX(uint8_t operand) {
  // X -> M
  // Flags changed: 

  prepWrite(x);
}

void R6502::opSTY(uint8_t operand) {
  // Y -> M
  // Flags changed: 

  prepWrite(y);
}

void R6502::opTAX(uint8_t operand) {
  // A -> X
  // Flags changed: Z N

  setX(accumulator);
  setFlags(
    Z | N,
    isZero(x) |
    isNegative(x)
  );
}

void R6502::opTAY(uint8_t operand) {
  // A -> Y
  // Flags changed: Z N

  setY(accumulator);
  setFlags(
    Z | N,
    isZero(y) |
    isNegative(y)
  );
}

void R6502::opTSX(uint8_t operand) {
  // SP -> X
  // Flags changed: Z N

  setX(sp);
  setFlags(
    Z | N,
    isZero(x) |
    isNegative(x)
  );
}

void R6502::opTXA(uint8_t operand) {
  // X -> A
  // Flags changed: Z N

  setAccumulator(x);
  setFlags(
    Z | N,
    isZero(accumulator) |
    isNegative(accumulator)
  );
}

void R6502::opTXS(uint8_t operand) {
  // X -> SP
  // Flags changed: Z N

  setSP(x);
  // NOT NEEDED: setFlags(Z | N, isZero(sp) | isNegative(sp));
}

void R6502::opTYA(uint8_t operand) {
  // Y -> A
  // Flags changed: Z N

  setAccumulator(y);
  setFlags(
    Z | N,
    isZero(accumulator) |
    isNegative(accumulator)
  );
}









void R6502::modeIllegal() {
  
}

void R6502::opIllegal(uint8_t) { // Does nothing, illegal instruction
  return;
}




