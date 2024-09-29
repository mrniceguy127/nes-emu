#ifndef BYTE_UTILS
#define BYTE_UTILS

#include <cstdint>

namespace util {
  namespace byte {
    /**
     * @brief sets bits of a byte based on a mask byte and a byte representing what to change them to.
     * 
     * @param bitsToChange The byte mask.
     * @param value The values to set the bits specified by the mask to.
     * @param byte The original byte to modify.
     * @return uint8_t 
     */
    uint8_t setBitsOfByte(uint8_t bitsToChange, uint8_t value, uint8_t byte);

    /**
     * @brief Get the low byte of a double byte. lo byte is larger address than hi.
     * 
     * @param dbyte The double byte.
     * @return uint8_t The low byte.
     */
    uint8_t lo(uint16_t dbyte);

    /**
     * @brief Get the low byte of a double byte. lo byte is larger address than hi. Returns as double byte.
     * 
     * @param dbyte The double byte.
     * @return uint16_t the low byte.
     */
    uint16_t lo16(uint16_t dbyte);

    /**
     * @brief Get the high byte of a double byte. hi byte is smaller address than lo.
     * 
     * @param dbyte The double byte.
     * @return uint8_t The low byte.
     */
    uint8_t hi(uint16_t dbyte);

    /**
     * @brief Get the high byte of a double byte. hi byte is smaller address than lo. Returns as double byte.
     * 
     * @param dbyte The double byte.
     * @return uint16_t The low byte.
     */
    uint16_t hi16(uint16_t dbyte);

    /**
     * @brief Convert a byte to a dbyte.
     * 
     * @param lo 
     * @return uint16_t 
     */
    uint16_t dbyte(uint8_t lo);

    /**
     * @brief Convert two bytes to a dbyte.
     * 
     * @param hi 
     * @param lo 
     * @return uint16_t 
     */
    uint16_t dbyte(uint8_t hi, uint8_t lo);

    /**
     * @brief Is byte a zero?
     * 
     * @param byte 
     * @return uint8_t - Returns 0x01 (true) if zero and 0x00 (false) if not zero.
     */
    uint8_t isZero(uint8_t);

    /**
     * @brief Is double byte a zero?
     * 
     * @param byte 
     * @return uint8_t - Returns 0x01 flag (true) if zero and 0x00 (false) if not zero.
     */
    uint8_t isZero(uint16_t);

    /**
     * @brief Is byte negative?
     * 
     * @param byte 
     * @return uint8_t - Returns 0x01 (true) if negative and 0x00 (false) if not negative.
     */
    uint8_t isNegative(uint8_t);

    /**
     * @brief Is double byte negative?
     * 
     * @param byte 
     * @return uint8_t - Returns 0x01 (true) if negative and 0x00 (false) if not negative.
     */
    uint8_t isNegative(uint16_t);

    /**
     * @brief Is double byte indicative of a carry occuring?
     * 
     * @param byte 
     * @return uint8_t - Returns 0x01 (true) if a carry occured and 0x00 (false) if no carry occured.
     */
    uint8_t isCarry(uint16_t);
  }
}




#endif