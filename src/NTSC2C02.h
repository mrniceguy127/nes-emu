#include <cstdint>
#include <array>
#include <fstream>

void loadPatternTableFromFile(std::array<uint8_t, 0x1000>& patternTable0, std::array<uint8_t, 0x1000>& patternTable1) {
  const char* filePath = "./src/mario.nes";
  std::ifstream file(filePath, std::ios::binary);

  if (!file.is_open()) {
    std::cerr << "Failed to open file: " << filePath << std::endl;
    return;
  }

  const size_t buffer_size = 1024;
  unsigned int page = 0;
  std::vector<char> buffer(buffer_size);
  char header[0x10];
  file.read(header, 0x10);
  std::cout << "Header: " << header << std::endl;
  uint32_t startAddress = 0x10;
  uint8_t trainerPresent = ((uint8_t) header[0x06]) & 0x04;
  if (trainerPresent) {
    startAddress += 0x200;
  }
  uint32_t prgRomSize = ((uint32_t) header[0x04]) * 0x4000;
  startAddress += prgRomSize;
  std::cout << "Start Address: " << std::hex << startAddress << std::endl;
  //uint16_t chrRomSize = header[0x05] * 0x2000;
  uint16_t patternTableSize = 0x1000;
  file.seekg(startAddress, std::ios::beg);
  file.read(reinterpret_cast<char*>(patternTable0.data()), patternTableSize);
  file.read(reinterpret_cast<char*>(patternTable1.data()), patternTableSize);
  //std::cout << "Pattern Table 0: " << (int) patternTable0[0] << std::endl;

  if (file.fail() && !file.eof()) {
    std::cerr << "Error reading file: " << filePath << std::endl;
    file.close();
    return;
  }

  file.close();
}


struct Color {
  uint8_t r = 0x00;
  uint8_t g = 0x00;
  uint8_t b = 0x00;
};

uint16_t calcLocation(uint16_t x, uint16_t y, uint16_t rowSize) {
  return (y * rowSize) + x;
}

class Tile {
  private:
    // color palette references
    uint8_t currentPalette[0x04] = {
      0x21, 0x36, 0x17, 0x0F
    };
    std::array<uint8_t, 0x8 * 0x8> tileData;
  public:
    void loadTile(uint16_t tileNum, std::array<uint8_t, 0x1000>& patternTable0, std::array<uint8_t, 0x1000>& patternTable1) {
      uint16_t tileAddress = tileNum * 0x10;
      std::array<uint8_t, 0x1000>& patternTable = patternTable0;
      if (tileNum > 0xFF) {
        patternTable = patternTable1;
        tileAddress = (tileNum - 0x100) * 0x10;
      }
      for (uint16_t j = 0; j < 0x08; j++) {
        for (uint16_t i = 0; i < 0x08; i++) {
          uint8_t p0 = (patternTable[tileAddress + j] >> (0x07 - i)) & 0x01;
          uint8_t p1 = (patternTable[tileAddress + 0x08 + j] >> (0x07 - i)) & 0x01;
          tileData[calcLocation(i, j, 0x08)] = (p1 << 1) | p0;
        }
      }
    }

    Color getColor(uint16_t pixel, Color * palette) {
      return palette[currentPalette[tileData[pixel]]];
    }
};




class NTSC2C02 {
  private:
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

    std::array<uint8_t, 0xF00> unused0;

    // mirror of palette
    //std::array<Color, 0x40> &palleteMirror = palette;

  public:
    Tile generateTile(uint32_t tileNum) {
      Tile tile = Tile();
      tile.loadTile(tileNum, patternTable0, patternTable1);
      return tile;
    }

    void generatePixMap(std::array<Color, 0x100 * 0x80>& pixMap) {
      loadPatternTable();
      //patternTable0.fill(0xFF);
      //patternTable1.fill(0x00);
      //patternTable0[0] = 0x00;
      for (uint32_t tileNum = 0; tileNum < 0x200; tileNum++) {
        Tile tile = generateTile(tileNum);
        int32_t offset = 0;
        if (tileNum > 0xFF) offset = 0x80;
        for (uint32_t j = 0; j < 0x08; j++) {
          for (uint32_t i = 0; i < 0x08; i++) {
            Color color = tile.getColor(calcLocation(i, j, 0x08), palette);
            uint32_t tileXOffset = (tileNum & 0x0F) * 0x08;
            uint32_t tileYOffset = ((tileNum & 0xF0) >> 0x04) * 0x08;
            uint32_t pixelXOffset = i;
            uint32_t pixelYOffset = j;
            uint32_t tileOffset = calcLocation(tileXOffset + pixelXOffset, tileYOffset + pixelYOffset, 0x100);
            uint32_t location = tileOffset + offset;
            pixMap[location] = color;
          }
        }
      }
    }

    void loadPatternTable() {
      loadPatternTableFromFile(patternTable0, patternTable1);
    }
};
