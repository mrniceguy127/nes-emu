#include "NESIncludes.h"

class Bus {
  public:
    Bus();
    ~Bus();
  public:
    std::array<uint8_t, 0x10000> ram;
  public:
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t data);
};
