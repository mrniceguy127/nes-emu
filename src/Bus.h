#include "NESIncludes.h"

class Bus {
  public:
    Bus();
    ~Bus();
  private:
    R6502 cpu;
    std::array<uint8_t, 64*1024> ram;
  public:
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t data);
};
