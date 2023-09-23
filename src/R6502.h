#include "NESIncludes.h"

class Memory; // Fixes circular inclusion problem

class R6502 {
  public:
    R6502(Memory&);
    ~R6502();
  public:
    // Initialization for outside programmer
    void init();
  public:
    // External events
    void clock();
    void RES();
    void IRQ();
    void NMI();
  private:
    Memory memory;
    uint8_t read(uint16_t addr);
    uint16_t read16(uint16_t addr);
    uint8_t readPC();
    uint16_t readPC16();
    void write(uint16_t addr, uint8_t data);
  private:
    // Useful variables
    uint8_t opcode = 0x00;
    uint16_t absAddr = 0x0000;
    uint16_t relAddr = 0x0000;
    uint8_t operand = 0x00;
    uint16_t tmp = 0x0000;

    uint16_t cycles = 0; // Cycles remaining for instruction. Will loop until 0.... removing, notes in doCycles implementation
    uint64_t totalCyclesPassed = 0;

    // Useful methods
    uint8_t fetchOperand();
  private:
    // Registers
    uint8_t accumulator = 0x00; // Accumulator
    uint8_t x = 0x00; // X Index register
    uint8_t y = 0x00; // Y Index register
    uint16_t pc = 0x0000; // Program Counter (16 bits)
    uint8_t sp = 0x00; // Stack pointer
    
    
    // Flags
    uint8_t P = 0x00; // Processor Status

    enum FLAGS { // Never considered using enums for bit manipulation. Credit to OneLoneCoder for this strategy.
      N = 0x01 << 7, // Negative?
      V = 0x01 << 6, // Overflow?
      U = 0x01 << 5, // UNUSED
      B = 0x01 << 4, // BRK command?
      D = 0x01 << 3, // Decimal mode?
      I = 0x01 << 2, // IRQ disable?
      Z = 0x01 << 1, // Result zero?
      C = 0x01 << 0  // Carry?
    };

    uint8_t getFlag(FLAGS flag);
    uint8_t setBitsOfByte(uint8_t bitsToChange, uint8_t value, uint8_t byte);
    void setFlags(uint8_t flags, uint8_t value);
    void setFlags(uint8_t flags);

  private:
    struct Instruction {
      //char mnemonic[4];
      void (R6502::*addressMode)(void) = nullptr;
      void (R6502::*operation)(void) = nullptr;
      uint8_t machineCycles = 0;
    };

    std::vector<Instruction> instructionMatrix;

  private:
    // Utility functions
    uint8_t pullStack();
    uint16_t pullStack16();
    void pushStack(uint8_t byte);
    void pushStack16(uint16_t dbyte);
    static uint8_t isZero(uint8_t);
    static uint8_t isZero(uint16_t);
    static uint8_t isNegative(uint8_t);
    static uint8_t isNegative(uint16_t);
    static uint8_t isCarry(uint16_t);
    void doCycle(); // Emulate cycle. Useful for capturing cycle "events"
    void doRelBranch(); // Relative branching is all done the same...
    uint8_t extraCyclePrepped = 0x00;
    void prepExtraCycle();
    void doPossibleExtraCycle();
    uint16_t cyclesPassed(); // Get total cycles passed...
    void setPC(uint16_t);
    void incPC();
    void decPC();
    void setSP(uint8_t);
    void incSP();
    void decSP();
    void setX(uint8_t);
    void incX();
    void decX();
    void setY(uint8_t);
    void incY();
    void decY();
    void setAccumulator(uint8_t);
    void setP(uint8_t);

  private:
    // Events... Useful for logging, etc.
    void onRegisterUpdate();

  private:
    // Addressing modes
    void IMM();
    void ABS();
    void ABX();
    void ABY();
    void IMP();
    void ACC();
    void ZP0();
    void ZPX();
    void ZPY();
    void REL();
    void IZX();
    void IZY();
    void IND();

  private:
    void ADC();
    void AND();
    void ASL();
    void BCC();
    void BCS();
    void BEQ();
    void BIT();
    void BMI();
    void BNE();
    void BPL();
    void BRK();
    void BVC();
    void BVS();
    void CLC();
    void CLD();
    void CLI();
    void CLV();
    void CMP();
    void CPX();
    void CPY();
    void DEC();
    void DEX();
    void DEY();
    void EOR();
    void INC();
    void INX();
    void INY();
    void JMP();
    void JSR();
    void LDA();
    void LDX();
    void LDY();
    void LSR();
    void NOP();
    void ORA();
    void PHA();
    void PHP();
    void PLA();
    void PLP();
    void ROL();
    void ROR();
    void RTI();
    void RTS();
    void SBC();
    void SEC();
    void SED();
    void SEI();
    void STA();
    void STX();
    void STY();
    void TAX();
    void TAY();
    void TSX();
    void TXA();
    void TXS();
    void TYA();

    void XXX();
};
