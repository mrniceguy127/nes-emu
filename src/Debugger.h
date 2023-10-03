#include "NESIncludes.h"

class Debugger {
  protected:
    R6502* cpu;
  public:
    Debugger(R6502* c);
    ~Debugger();
  public:
    /**
     * @brief Show the current CPU state.
     * 
     */
    virtual void showState() = 0;

    /**
     * @brief Step function for CPU.
     * 
     */
    void step();
};

class ConsoleDebugger : public Debugger {
    public:
      ConsoleDebugger(R6502* cpu);
      ~ConsoleDebugger();
    public:
      /**
       * @brief Show the current CPU state in console.
       * 
       */
      void showState() override;
};