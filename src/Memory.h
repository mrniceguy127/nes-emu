#include "NESIncludes.h"

class AddressMappingFunction {
  private:
    std::array<uint8_t, 0x10000>& memory;
  public:
    explicit AddressMappingFunction(std::array<uint8_t, 0x10000>& memory);
    virtual uint8_t read(uint16_t addr);
    virtual void write(uint16_t addr, uint8_t data);
};
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
  /** 
   * @brief Address mappings
   * 
   */
  std::array<AddressMappingFunction*, 0x10000> addressMap;

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

    void mapAddress(uint16_t addr, AddressMappingFunction* addressMappingFunction);

    void mapAddressRange(uint16_t startAddr, uint16_t endAddr, AddressMappingFunction* addressMappingFunction);
};