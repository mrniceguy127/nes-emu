#include "ByteUtils.h"

uint8_t util::byte::setBitsOfByte(uint8_t bitsToChange, uint8_t value, uint8_t byte) {
  return (byte & ~bitsToChange) | (value & bitsToChange);
}

uint16_t util::byte::lo16(uint16_t dbyte) {
  return dbyte & 0x00FF;
}

uint8_t util::byte::lo(uint16_t dbyte) {
  return (uint8_t) lo16(dbyte);
}

uint16_t util::byte::hi16(uint16_t dbyte) {
  return dbyte & 0xFF00;
}

uint8_t util::byte::hi(uint16_t dbyte) {
  return (uint8_t) (dbyte >> 8);
}

uint16_t util::byte::dbyte(uint8_t lo) {
  return lo16((uint16_t) lo);
}

uint16_t util::byte::dbyte(uint8_t hi, uint8_t lo) {
  return (dbyte(hi) << 8) | dbyte(lo);
}

uint8_t util::byte::isZero(uint8_t byte) {
  return byte ? 0 : 1;
}

uint8_t util::byte::isZero(uint16_t doubleByte) {
  return doubleByte ? 0 : 1;
}

uint8_t util::byte::isNegative(uint8_t byte) {
  return byte & 0x80;
}

uint8_t util::byte::isNegative(uint16_t doubleByte) {
  return lo(doubleByte & 0x0080);
}

uint8_t util::byte::isCarry(uint16_t doubleByte) {
  return hi(doubleByte);
}