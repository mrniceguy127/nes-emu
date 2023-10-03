#include "NESIncludes.h"

class Memory {
  public:
    Memory();
    ~Memory();
  public:
  /**
   * @brief Memory array.
   * 
   */
    std::array<uint8_t, 0x10000> ram;
  public:
  /**
   * @brief Read a byte given an address within the bounds of the RAM.
   * 
   * @param addr - The 16 bit address to read the byte from.
   * @return uint8_t - The byte at the address
   */
    uint8_t read(uint16_t addr);

    /**
     * @brief Write a byte given an address within the bounds of the RAM.
     * 
     * @param addr - The 16 bit address to write the byte to.
     * @param data - The byte to write at the address.
     */
    void write(uint16_t addr, uint8_t data);
};
