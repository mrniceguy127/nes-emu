#include "NESIncludes.h"

class Memory; // Fixes circular inclusion problem

class R6502 {
  public:
    R6502(Memory *);
    ~R6502();
  public:
    // Initialization for outside programmer

    /**
     * @brief Init CPU power on state
     * 
     */
    void powerOn();
  public:
    // External events

    /**
     * @brief Start CPU clock.
     * 
     */
    void clock();

    /**
     * @brief Reset command.
     * 
     * https://wiki.nesdev.org/w/index.php?title=CPU_power_up_state
     * (Page 2 under RESET (RES)) http://archive.6502.org/datasheets/rockwell_r650x_r651x.pdf
     * 
     */
    void RES();

    /**
     * @brief IRQ interrupt sequence command
     * 
     * http://archive.6502.org/datasheets/synertek_programming_manual.pdf - p. 131
     * https://www.nesdev.org/wiki/CPU_interrupts
     * 
     */
    void IRQ();

    /**
     * @brief NMI interrupt sequence command
     * 
     * http://archive.6502.org/datasheets/synertek_programming_manual.pdf - p. 131
     * https://www.nesdev.org/wiki/CPU_interrupts
     * 
     */
    void NMI();

  public:
    Memory* memory;

    /**
     * @brief Read byte at address
     * 
     * @param addr Address of data
     * @return uint8_t The data
     */
    uint8_t read(uint16_t addr);

    /**
     * @brief Read a double byte and handle the 6502's little endian nature.
     * 
     * @param addr Initial address of double byte.
     * @return uint16_t The double byte.
     */
    uint16_t read16(uint16_t addr);

    /**
     * @brief Read byte at address in PC and then increment PC
     * 
     * @return uint8_t The data
     */
    uint8_t readPC();


    /**
     * @brief Read byte at address in PC, increment PC, and then repeat again for the double byte.
     * 
     * @return uint16_t The double byte.
     */
    uint16_t readPC16();

    /**
     * @brief Write a byte at an address.
     * 
     * @param addr The address to write to.
     * @param data The data to write.
     */
    void write(uint16_t addr, uint8_t data);

    /**
     * @brief Prepare the cpu for a write if applicable.
     * 
     * @param byte 
     * @return uint8_t 
     */
    void prepWrite(uint8_t data);
    void prepWrite(uint16_t data);

    void opWrite();

  public:
    // Useful variables
    uint16_t fetchAddress = 0x0000;
    uint8_t opcode = 0x00;
    uint16_t tmp = 0x0000;
    uint8_t operand = 0x00;

    uint8_t enableWrite = 0x00;
    uint8_t writeReg = 0x00;

    uint64_t totalCyclesPassed = 0;

    // Useful methods

    /**
     * @brief Reads from the currently relevant absolute address.
     * 
     * This is almost always the operand of an instruction)
     * 
     * @return uint8_t - The operand in most cases. 
     */
    void fetchOperand();
  public:
    // Registers
    uint8_t accumulator = 0x00; // Accumulator
    uint8_t x = 0x00; // X Index register
    uint8_t y = 0x00; // Y Index register
    uint16_t pc = 0x0000; // Program Counter (16 bits)
    uint8_t sp = 0x00; // Stack pointer

    // Flags
    uint8_t P = 0x00; // Processor Status

    enum FLAGS {
      N = 0x80, // Negative?
      V = 0x40, // Overflow?
      U = 0x20, // UNUSED
      B = 0x10, // BRK command?
      D = 0x08, // Decimal mode?
      I = 0x04, // IRQ disable?
      Z = 0x02, // Result zero?
      C = 0x01  // Carry?
    };

    /**
     * @brief Get the Flag with a value set or not.
     * 
     * @param flag The flag to get as a value.
     * @param value Boolean value to set the return flag to.
     * @return FLAGS 
     */
    static uint8_t getFlagByteAs(FLAGS flag, uint8_t value);

    /**
     * @brief returns the BIT value of a flag
     * 
     * @param flag The flag of the bit you want.
     * @return uint8_t 1 or 0.
     */
    uint8_t getFlag(FLAGS flag);

    /**
     * @brief Sets flags to a specific value.
     * 
     * @param flags The flags to set. e.g. Z | N | C to set the Z, N, and C flags.
     * @param value The value to set them to. i.e. 1 or 0
     */
    void setFlags(uint8_t flags, uint8_t value);

    /**
     * @brief Set specific flags to 1.
     * 
     * @param flags The flags to set. e.g. Z | N | C to set the Z, N, and C flags to one.
     */
    void setFlags(uint8_t flags);

    static const char* opMnemonics[57];
    static const char* addressModeNames[14];

  public:
    struct State {
      uint8_t accumulator = 0x00;
      uint8_t x = 0x00;
      uint8_t y = 0x00;
      uint16_t pc = 0x0000;
      uint8_t sp = 0x00;
      uint8_t P = 0x00;
    }; 

    /**
     * @brief Get the state of registers
     * 
     * @return State 
     */

    State getState();

    enum MODES {
      ILLMODE, // emulator utility. Not a real address mode

      IMMEDIATE,
      ABSOLUTE, ABSOLUTEX, ABSOLUTEY,
      IMPLIED, ACCUMULATOR,
      ZEROPAGE, ZEROPAGEX, ZEROPAGEY,
      RELATIVE,
      INDIRECT, INDIRECTX, INDIRECTY
    };

    enum OPS {
      ILLOP, // emulator utility. Not a real operation

      ADC, AND, ASL, BCC, BCS, BEQ, BIT, BMI,
      BNE, BPL, BRK, BVC, BVS, CLC, CLD, CLI,
      CLV, CMP, CPX, CPY, DEC, DEX, DEY, EOR,
      INC, INX, INY, JMP, JSR, LDA, LDX, LDY,
      LSR, NOP, ORA, PHA, PHP, PLA, PLP, ROL,
      ROR, RTI, RTS, SBC, SEC, SED, SEI, STA,
      STX, STY, TAX, TAY, TSX, TXA, TXS, TYA
    };

    
    typedef void (R6502::*ModeFunc)();
    static const ModeFunc modeFuncs[14];

    typedef void (R6502::*OpFunc)();
    static const OpFunc opFuncs[57];

    struct Instruction {
      MODES addressMode = ILLMODE;
      OPS operation =  ILLOP;
    };

    static const Instruction NULL_INSTRUCTION;

    struct InstructionMetadata {
      const char* mnemonic;
      const char* addressModeName;
    };

    /**
     * @brief Get the address mode name for a given address mode enum
     * 
     * @return const char* 
     */
    static const char* getAddressModeName(MODES);

    /**
     * @brief Get the operation mnemonic given an operation enum
     * 
     * @return const char* 
     */

    static const char* getOpMnemonic(OPS);
    
    /**
     * @brief Get the Instruction Meta Data for a given instruction
     * 
     * Returns the mnemonic for the operation and the address mode name
     * 
     * @return InstructionMetadata 
     */
    static InstructionMetadata getInstructionMetadata(Instruction&);

    /**
     * @brief Get the Instruction Meta Data for a given op code
     * 
     * Returns the mnemonic for the operation and the address mode name
     * 
     * @return InstructionMetadata 
     */
    static InstructionMetadata getInstructionMetadata(uint8_t);
  private:
    static const Instruction instructionMatrix[0x100];
    Instruction currentInstruction = NULL_INSTRUCTION;

    /**
     * @brief Execute code requiured for given address mode
     * 
     * @param mode - The mode.
     */
    void doAddressMode(MODES);


    /**
     * @brief Executes the given operation
     * 
     * @param op - The operation.
     */
    void doOperation(OPS);
  public:
    /**
     * @brief Execute a given instruction.
     * 
     * @param instruction - The instruction
     */
    void doInstruction(const Instruction&);

    /**
     * @brief Do next instruction pointed at by the PC.
     * 
     */
    void doNextInstruction();

    /**
     * @brief Get the 6502 Instruction Matrx 
     * 
     * @return Instruction*
     */
    static const Instruction* getInstructionMatrix();

    /**
     * @brief Get the current Op Code 
     * 
     * @return uint8_t - Current opcode
     */
    uint8_t getCurrentOpCode();

  private:
    // Utility functions

    /**
     * @brief Used for pulling from the stack in a "chain" fashion. Stack pulling logic is difficult to fit into a function elegantly.
     * 
     * @return uint8_t 
     */
    uint8_t pullStackChain();

    /**
     * @brief Used for pulling from the stack in a "chain" fashion for a double byte
     * 
     * @return uint8_t 
     */
    uint16_t pullStackChain16();

    /**
     * @brief End the stack pulling chain.
     * 
     */
    void endPullStackChain();

    /**
     * @brief Push byte onto the stack.
     * 
     * @param byte The value to push to the stack.
     */
    void pushStack(uint8_t byte);

    /**
     * @brief Push double byte to the stack.
     * 
     * @param dbyte The double byte to push to the stack.
     */
    void pushStack16(uint16_t dbyte);

    /**
     * @brief Is byte a zero?
     * 
     * @param byte 
     * @return uint8_t - Returns the Zero flag (true) if zero and zero (false) if not zero.
     */
    static uint8_t isZero(uint8_t);

    /**
     * @brief Is double byte a zero?
     * 
     * @param byte 
     * @return uint8_t - Returns the Zero flag (true) if zero and zero (false) if not zero.
     */
    static uint8_t isZero(uint16_t);

    /**
     * @brief Is byte negative?
     * 
     * @param byte 
     * @return uint8_t - Returns the Negative flag (true) if negative and zero (false) if not negative.
     */
    static uint8_t isNegative(uint8_t);

    /**
     * @brief Is double byte negative?
     * 
     * @param byte 
     * @return uint8_t - Returns the Negative flag (true) if negative and zero (false) if not negative.
     */
    static uint8_t isNegative(uint16_t);

    /**
     * @brief Is double byte indicative of a carry occuring?
     * 
     * @param byte 
     * @return uint8_t - Returns the Carry flag (true) if a carry occured and zero (false) if no carry occured.
     */
    static uint8_t isCarry(uint16_t);


    /**
     * @brief Executes when a cycle occurs.
     * 
     * Good for capturing clock cycles.
     * 
     */
    void doCycle();

    /**
     * @brief Executes when a cycle occurs.
     * 
     * Good for capturing clock cycles.
     * 
     * @param byte is extra?
     */
    void doCycle(uint8_t);

    uint8_t cyclesPassedThisInstruction = 0x00;
    uint8_t extraCyclesPassedThisInstruction = 0x00;

    /**
     * @brief Performs relative branching.
     * 
     * Very frequent operation in instructions...
     * Useful method for cutting down on bugs / repetition.
     * 
     */
    void doRelBranch();


    uint8_t extraCyclePrepped = 0x00;

    /**
     * @brief Preps an extra cycle if asked by address mode
     * 
     * Extra cycle will execute if instruction agrees on extra cycle.
     * 
     */
    void prepExtraCycle();

    /**
     * @brief Performs extra clock cycle if agreed upon by the address mode.
     * 
     */
    void doPossibleExtraCycle();

    /**
     * @brief Set the value in the PC directly.
     * 
     * @param addr The address to store in the PC.
     */
    void setPC(uint16_t);

    /**
     * @brief Increment PC.
     * 
     */
    void incPC();

    /**
     * @brief Decrement the PC.
     * 
     */
    void decPC();

    /**
     * @brief Set the stack pointer directly.
     * 
     * @param byte New pointer value. 
     */
    void setSP(uint8_t);

    /**
     * @brief Increment stack pointer.
     * 
     */
    void incSP();

    /**
     * @brief Decrement stack pointer.
     * 
     */
    void decSP();

    /**
     * @brief Set the X index register value directly.
     * 
     * @param byte New X index value.
     */
    void setX(uint8_t);

    /**
     * @brief Increment the X index register.
     * 
     */
    void incX();

    /**
     * @brief Decrement the X index register.
     * 
     */
    void decX();
    
    /**
     * @brief Set the Y index register directly.
     * 
     * @param byte New Y index value.
     */
    void setY(uint8_t);


    /**
     * @brief Increment the Y index register.
     * 
     */
    void incY();

    /**
     * @brief Decrement the Y index register.
     * 
     */
    void decY();

    /**
     * @brief Set the value of the accumulator.
     * 
     * @param byte New accumulator value.
     */
    void setAccumulator(uint8_t);

    /**
     * @brief Set processor status directly.
     * 
     * @param byte New processor status.
     */
    void setP(uint8_t);

  public:
    /**
     * @brief Get the number of Cycles Passed This Instruction
     * 
     * @return uint8_t 
     */
    uint8_t getCyclesPassedThisInstruction();

    /**
     * @brief Get the number of extra Cycles Passed This Instruction
     * 
     * @return uint8_t 
     */
    uint8_t getExtraCyclesPassedThisInstruction();

  private:
    // Event handlers... Useful for logging, etc.

    /**
     * @brief Called everytime a register updates.
     * 
     * Useful for logging.
     * 
     */
    void onRegisterUpdate();

  private:
    // Addressing modes

    /**
     * @brief Immediate addressing mode.
     *
     * Next byte has operand. get current pc, then increment.
     * 
     */
    void modeImmediate();

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
    void modeAbsolute();

    /**
     * @brief Absolute X addressing mode.
     * 
     */
    void modeAbsoluteX();

    /**
     * @brief Absolute Y addressing mode.
     * 
     */
    void modeAbsoluteY();


    /**
     * @brief Implied addressing mode.
     * 
     */
    void modeImplied();

    /**
     * @brief Accumulator addressing mode.
     * 
     * It's just IMP...
     * 
     */
    void modeAccumulator();

    /**
     * @brief Zero Page addressing mode.
     * 
     */
    void modeZeroPage();


    /**
     * @brief Zero Page (X-indexed) addressing mode.
     * 
     */
    void modeZeroPageX();

    /**
     * @brief Zero Page (Y-indexed) addressing mode.
     * 
     */
    void modeZeroPageY();

    /**
     * @brief Relative addressing mode.
     * 
     */
    void modeRelative();

    /**
     * @brief Indirect (X-indexed) addressing mode.
     * 
     */
    void modeIndirectX();

    /**
     * @brief Indirect (X-indexed) addressing mode.
     * 
     */
    void modeIndirectY();

    /**
     * @brief Indirect addressing mode.
     * 
     * Intentionally bugged because that's the way it is on the 6502 itself.
     * hnesdev.icequake.net/6502bugs.txt:
     *
     */
    void modeIndirect();

  private:
    // Opertions


    void opADC();
    void opAND();
    void opASL();
    void opBCC();
    void opBCS();
    void opBEQ();
    void opBIT();
    void opBMI();
    void opBNE();
    void opBPL();
    void opBRK();
    void opBVC();
    void opBVS();
    void opCLC();
    void opCLD();
    void opCLI();
    void opCLV();
    void opCMP();
    void opCPX();
    void opCPY();
    void opDEC();
    void opDEX();
    void opDEY();
    void opEOR();
    void opINC();
    void opINX();
    void opINY();
    void opJMP();
    void opJSR();
    void opLDA();
    void opLDX();
    void opLDY();
    void opLSR();
    void opNOP();
    void opORA();
    void opPHA();
    void opPHP();
    void opPLA();
    void opPLP();
    void opROL();
    void opROR();
    void opRTI();
    void opRTS();
    void opSBC();
    void opSEC();
    void opSED();
    void opSEI();
    void opSTA();
    void opSTX();
    void opSTY();
    void opTAX();
    void opTAY();
    void opTSX();
    void opTXA();
    void opTXS();
    void opTYA();

  private:
    // Illegal instruction handling

    /**
     * @brief Executes when an illegal address mode is executed
     * 
     */
    void modeIllegal();

    /**
     * @brief Executes when an illegal operation is executed
     * 
     */
    void opIllegal();
};
