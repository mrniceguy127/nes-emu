#include "NESIncludes.h"

class DebuggerInputStrategy {
  public:
    virtual void getStepInput(char*, const size_t) = 0;
};

class DebuggerOutputStrategy {
  public:
    virtual void showState(R6502* cpu) = 0;
};

class DebuggerConsoleInputStrategy : public DebuggerInputStrategy {
  public:
    void getStepInput(char*, const size_t) override;
};

class DebuggerConsoleOuptutStrategy : public DebuggerOutputStrategy {
  public:
    void showState(R6502* cpu) override;
};

class Debugger {
  protected:
    R6502* cpu;
    DebuggerInputStrategy* inputHandler;
    DebuggerOutputStrategy* outputHandler;
  public:
    Debugger(R6502* c);
    ~Debugger();
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