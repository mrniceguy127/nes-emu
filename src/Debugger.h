#include "NESIncludes.h"

class DebuggerInputStrategy {
  public:
    /**
     * @brief Get the Step Input objectAbstract method for getting input from user to proceed with stepping instruction
     * 
     */
    virtual void getStepInput(char*, const size_t) = 0;
};

class DebuggerOutputStrategy {
  protected:
    uint16_t lastPC = 0x0000;
  public:
    /**
     * @brief Abstaract method for displaying CPU state
     * 
     * @param cpu 
     */
    virtual void showState(R6502* cpu, R6502::State previousState) = 0;

    /**
     * @brief Abstract method for showing debugger step output
     * 
     */
    virtual void step() = 0;
};

class DebuggerConsoleInputStrategy : public DebuggerInputStrategy {
  public:
    /**
     * @brief Get input from the user to proceed with stepping instruction
     * 
     */
    void getStepInput(char*, const size_t) override;
};

class DebuggerConsoleOuptutStrategy : public DebuggerOutputStrategy {
  public:
    /**
     * @brief Show the current CPU state in console
     * 
     */
    void showState(R6502* cpu, R6502::State previousState) override;
    void step() override;
};

class Debugger {
  protected:
    R6502* cpu;
    DebuggerInputStrategy* inputHandler;
    DebuggerOutputStrategy* outputHandler;
    uint8_t hitBreak = 0x00;
    uint8_t stackTraceEnabled = 0x00;
    uint16_t breakPoint = 0x0000;
    uint8_t breakPointEnabled = 0x00;
    R6502::State previousState;
  public:
    Debugger(R6502* c);
  public:
    /**
     * @brief Show the current CPU state.
     * 
     */
    void showState();

    /**
     * @brief Step function for CPU.
     * 
     */
    void step();

    /**
     * @brief Run the cpu with debugger attached.
     * 
     */
     void run();

     /**
      * @brief Pause the debugger
      * 
      */
     void pause();

      /**
        * @brief Set the Break Point object
        * 
        * @param bp 
        */
      void setBreakPoint(uint16_t bp);

      /**
       * @brief Enable stack trace output
       * 
       */
      void enableStackTrace();
};

class ConsoleDebugger : public Debugger {
    public:
      ConsoleDebugger(R6502* cpu);
};