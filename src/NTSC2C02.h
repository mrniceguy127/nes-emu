#include <cstdint>
#include <array>
#include <fstream>
#include <vector>
#include "NESIncludes.h"

#ifndef NTSC2C02_H
#define NTSC2C02_H

void loadPatternTableFromFile(std::array<uint8_t, 0x1000>& patternTable0, std::array<uint8_t, 0x1000>& patternTable1);


struct Color {
  uint8_t r = 0x00;
  uint8_t g = 0x00;
  uint8_t b = 0x00;
};

uint16_t calcLocation(uint16_t x, uint16_t y, uint16_t rowSize);

class Tile {
  private:
    // color palette references
    uint8_t currentPalette[0x04] = {
      0x21, 0x36, 0x17, 0x0F
    };
    std::array<uint8_t, 0x8 * 0x8> tileData;
  public:
    void loadTile(uint16_t tileNum, std::array<uint8_t, 0x1000>& patternTable0, std::array<uint8_t, 0x1000>& patternTable1);

    Color getColor(uint16_t pixel, Color * palette);
};



class Register {
  private:
    uint8_t reg = 0x00;
  public:
    void set(uint8_t val);
    uint8_t get();
    void setFlags(uint8_t byte, bool val);
    void setFlags(uint8_t byte);
    bool getFlag(uint8_t bit);
};


class NTSC2C02 {
  public:
    Color palette[0x40] = {
      { 0x62, 0x62, 0x62 }, { 0x00, 0x2c, 0x7c }, { 0x11, 0x15, 0x9c }, { 0x36, 0x03, 0x9c }, { 0x55, 0x00, 0x7c }, { 0x67, 0x00, 0x44 }, { 0x67, 0x07, 0x03 }, { 0x55, 0x1c, 0x00 }, { 0x36, 0x32, 0x00 }, { 0x11, 0x44, 0x00 }, { 0x00, 0x4e, 0x00 }, { 0x00, 0x4c, 0x03 }, { 0x00, 0x40, 0x44 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
      { 0xab, 0xab, 0xab }, { 0x12, 0x60, 0xce }, { 0x3d, 0x42, 0xfa }, { 0x6e, 0x29, 0xfa }, { 0x99, 0x1c, 0xce }, { 0xb1, 0x1e, 0x81 }, { 0xb1, 0x2f, 0x29 }, { 0x99, 0x4a, 0x00 }, { 0x6e, 0x69, 0x00 }, { 0x3d, 0x82, 0x00 }, { 0x12, 0x8f, 0x00 }, { 0x00, 0x8d, 0x29 }, { 0x00, 0x7c, 0x81 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
      { 0xff, 0xff, 0xff }, { 0x60, 0xb2, 0xff }, { 0x8d, 0x92, 0xff }, { 0xc0, 0x78, 0xff }, { 0xec, 0x6a, 0xff }, { 0xff, 0x6d, 0xd4 }, { 0xff, 0x7f, 0x79 }, { 0xec, 0x9b, 0x2a }, { 0xc0, 0xba, 0x00 }, { 0x8d, 0xd4, 0x00 }, { 0x60, 0xe2, 0x2a }, { 0x47, 0xe0, 0x79 }, { 0x47, 0xce, 0xd4 }, { 0x4e, 0x4e, 0x4e }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
      { 0xff, 0xff, 0xff }, { 0xbf, 0xe0, 0xff }, { 0xd1, 0xd3, 0xff }, { 0xe6, 0xc9, 0xff }, { 0xf7, 0xc3, 0xff }, { 0xff, 0xc4, 0xee }, { 0xff, 0xcb, 0xc9 }, { 0xf7, 0xd7, 0xa9 }, { 0xe6, 0xe3, 0x97 }, { 0xd1, 0xee, 0x97 }, { 0xbf, 0xf3, 0xa9 }, { 0xb5, 0xf2, 0xc9 }, { 0xb5, 0xeb, 0xee }, { 0xb8, 0xb8, 0xb8 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }
    };

    std::array<uint8_t, 0x8> loadedPalettes = {0};

    std::array<uint8_t, 0x1000> patternTable0;
    std::array<uint8_t, 0x1000> patternTable1;

    std::array<uint8_t, 0x400> nameTable0;
    std::array<uint8_t, 0x400> nameTable1;

    // mirrors of first two name tables
    std::array<uint8_t, 0x400> &nameTable2 = nameTable0;
    std::array<uint8_t, 0x400> &nameTable3 = nameTable1;

    std::array<uint8_t, 0x40> attributeTable0;
    std::array<uint8_t, 0x40> attributeTable1;
    std::array<uint8_t, 0x40> attributeTable2;
    std::array<uint8_t, 0x40> attributeTable3;

    std::array<uint8_t, 0xF00> unused0;
    uint16_t scanLineCycle = 0;
    uint16_t scanLine = 261;
    uint8_t frame = 0;


    // mirror of palette
    //std::array<Color, 0x40> &palleteMirror = palette;

    void mapMemoryToTables();

  public:
    Memory * memory;
    Register * PPUCTRL = new Register();
    Register * PPUMASK = new Register();
    Register * PPUSTATUS = new Register();
    Register * OAMADDR = new Register();
    Register * OAMDATA = new Register();
    Register * PPUSCROLL = new Register();
    Register * PPUADDR = new Register();
    Register * PPUDATA = new Register();
    Register * OAMDMA = new Register();

    enum PPUFlags {
      CTRL_N0 = 0x01,
      CTRL_N1 = 0x02,
      CTRL_I = 0x04,
      CTRL_S = 0x08,
      CTRL_B = 0x10,
      CTRL_H = 0x20,
      CTRL_P = 0x40,
      CTRL_V = 0x80,

      MASK_g = 0x01,
      MASK_m = 0x02,
      MASK_M = 0x04,
      MASK_b = 0x08,
      MASK_s = 0x10,
      MASK_R = 0x20,
      MASK_G = 0x40,
      MASK_B = 0x80,

      STATUS_V = 0x80,
      STATUS_S = 0x40,
      STATUS_O = 0x20,
      STATUS_U4 = 0x10,
      STATUS_U3 = 0x08,
      STATUS_U2 = 0x04,
      STATUS_U1 = 0x02,
      STATUS_U0 = 0x01
    };

  public:
    NTSC2C02(Memory * mem);
    Tile generateTile(uint32_t tileNum);
    void generatePixMap(std::array<Color, 0x100 * 0x80>& pixMap);
    void loadPatternTable();
    void mapMemoryToCPUBus(Memory * mem);
    void tick();
};

class CPUToPPUAddressMappingFunction : public AddressMappingFunction {
  private:
    NTSC2C02 * ppu;
  public:
    CPUToPPUAddressMappingFunction(NTSC2C02 * ppu);
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t data);
};

class PPUAddressMappingFunction : public AddressMappingFunction {
  private:
    NTSC2C02 * ppu;
  public:
    PPUAddressMappingFunction(NTSC2C02 * ppu);
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t data);
};
#endif