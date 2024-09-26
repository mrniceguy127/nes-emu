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
  public:
    /**
     * @brief Abstaract method for displaying CPU state
     * 
     * @param cpu 
     */
    virtual void showState(R6502* cpu) = 0;
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
    void showState(R6502* cpu) override;
};

class Debugger {
  protected:
    R6502* cpu;
    DebuggerInputStrategy* inputHandler;
    DebuggerOutputStrategy* outputHandler;
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
};

class ConsoleDebugger : public Debugger {
    public:
      ConsoleDebugger(R6502* cpu);
};