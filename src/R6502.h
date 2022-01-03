#include "NESIncludes.h"

class Bus; // Fixes circular inclusion problem

class R6502 {
  public:
    R6502();
    ~R6502();
  public:
    // External events
    void clock();
    void reset();
    void irq();
    void nmi();

    void connectBus(Bus * bus);
  private:
    Bus * bus = nullptr;
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t data);
  private:
    // Useful variables
    uint16_t absAddr = 0x0000;
    uint16_t relAddr = 0x0000;
    uint8_t fetched = 0x00;
    uint16_t tmp = 0x0000;

    // Useful methods
    uint8_t fetch();
  private:
    // Registers
    uint8_t a = 0x00; // Accumulator
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
    void setFlag(FLAGS flag, uint8_t value);

  private:
    std::array<instruction, 0xF*0xF> instructionMatrix;

    struct instruction {
      char mnemonic[3];
      uint8_t (* addressMode)(void *);
      uint8_t (* operation)(void *);
    };

  private:
    // Addressing modes
    uint8_t IMM();
    uint8_t ABS();
    uint8_t ABX();
    uint8_t ABY();
    uint8_t IMP();
    uint8_t ZP0();
    uint8_t ZPX();
    uint8_t ZPY();
    uint8_t REL();
    uint8_t IZX();
    uint8_t IZY();
    uint8_t IND();

  private:
    uint8_t ADC();
    uint8_t AND();
    uint8_t ASL();
    uint8_t BCC();
    uint8_t BCS();
    uint8_t BEQ();
    uint8_t BIT();
    uint8_t BMI();
    uint8_t BNE();
    uint8_t BPL();
    uint8_t BRK();
    uint8_t BVC();
    uint8_t BVS();
    uint8_t CLC();
    uint8_t CLD();
    uint8_t CLI();
    uint8_t CLV();
    uint8_t CMP();
    uint8_t CPX();
    uint8_t CPY();
    uint8_t DEC();
    uint8_t DEX();
    uint8_t DEY();
    uint8_t EOR();
    uint8_t INC();
    uint8_t INX();
    uint8_t INY();
    uint8_t JMP();
    uint8_t JSR();
    uint8_t LDA();
    uint8_t LDX();
    uint8_t LDY();
    uint8_t LSR();
    uint8_t NOP();
    uint8_t ORA();
    uint8_t PHA();
    uint8_t PHP();
    uint8_t PLA();
    uint8_t PLP();
    uint8_t ROL();
    uint8_t ROR();
    uint8_t RTI();
    uint8_t RTS();
    uint8_t SBC();
    uint8_t SEC();
    uint8_t SED();
    uint8_t SEI();
    uint8_t STA();
    uint8_t STX();
    uint8_t STY();
    uint8_t TAX();
    uint8_t TAY();
    uint8_t TSX();
    uint8_t TXA();
    uint8_t TXS();
    uint8_t TYA();

    uint8_t XXX();
};
