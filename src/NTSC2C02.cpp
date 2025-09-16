#include <iostream>

#include <SDL3/SDL.h>

#include "NTSC2C02.h"
#include "NESIncludes.h"

int main() {
  std::array<Color, 0x100 * 0x80> screen;
  Memory * mem = new Memory();
  NTSC2C02 ppu = NTSC2C02(mem);
  ppu.generatePixMap(screen);
  
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window * window = SDL_CreateWindow("Pattern Table", 1024, 512, SDL_WINDOW_RESIZABLE);
  if (window == nullptr) {
      std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
      return 1;
  } else {
      std::cout << "SDL_CreateWindow Success" << std::endl;
  }
  SDL_Renderer * renderer = SDL_CreateRenderer(window, nullptr);
  if (renderer == nullptr) {
      std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
      return 1;
  } else {
      std::cout << "SDL_CreateRenderer Success" << std::endl;
  }

  std::cout << "begin" << std::endl;
// 2. Create a Texture with Streaming Access
    int width = 0x100;
    int height = 0x80;
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    if (texture == nullptr) {
        std::cerr << "SDL_CreateTexture Error: " << SDL_GetError() << "\n";
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // 3. Lock the Texture to Access Pixels
    void* pixels;
    int pitch;
    if (!SDL_LockTexture(texture, NULL, &pixels, &pitch)) {
        std::cerr << "SDL_LockTexture Error: " << SDL_GetError() << "\n";
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // 4. Modify Pixel Data
    // We'll create a simple gradient
    uint32_t * pixel_ptr = static_cast<uint32_t*>(pixels);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            uint16_t location = calcLocation(x, y, 0x100);
            Color color = screen[location];
            uint32_t r = color.r;
            uint32_t g = color.g;
            uint32_t b = color.b;
            uint32_t pixel_color = (r << 16) | (g << 8) | b | 0xFF000000;
            pixel_ptr[(y * 0x100) + x] = pixel_color;
        }
    }

    // 5. Unlock the Texture
    SDL_UnlockTexture(texture);



// 4. Main event loop
    bool running = true;
    SDL_Event event;
    while (running) {
        // Handle events on the event queue
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {  // User requests quit
                running = false;
            }
        }

        // Clear the screen with a color (e.g., Cornflower Blue)
        SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255); // RGBA
        SDL_RenderClear(renderer);

        // Render the Texture
        SDL_RenderTexture(renderer, texture, NULL, NULL);

        // Update the Screen
        SDL_RenderPresent(renderer);

        // Delay to control frame rate (e.g., ~60 FPS)
        SDL_Delay(16);
    }

    // 5. Clean up and quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
  return 0;
}





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

uint16_t calcLocation(uint16_t x, uint16_t y, uint16_t rowSize) {
  return (y * rowSize) + x;
}

void Tile::loadTile(uint16_t tileNum, std::array<uint8_t, 0x1000>& patternTable0, std::array<uint8_t, 0x1000>& patternTable1) {
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

Color Tile::getColor(uint16_t pixel, Color * palette) {
  return palette[currentPalette[tileData[pixel]]];
}


void Register::set(uint8_t val) {
  reg = val;
}

void Register::setFlags(uint8_t byte, bool val) {
  if (val) {
    reg |= byte;
  } else {
    reg &= ~byte;
  }
}

void Register::setFlags(uint8_t byte) {
  setFlags(byte, 0x1);
}

uint8_t Register::get() {
  return reg;
}

uint8_t Register::getFlag(uint8_t bit) {
  return (reg & bit) ? 0x1 : 0x0;
}


NTSC2C02::NTSC2C02(Memory * mem) : memory(mem) {
    mapMemoryToTables();
    //mapMemoryToCPUBus(mem);
};

Tile NTSC2C02::generateTile(uint32_t tileNum) {
  Tile tile = Tile();
  tile.loadTile(tileNum, patternTable0, patternTable1);
  return tile;
}

void NTSC2C02::generatePixMap(std::array<Color, 0x100 * 0x80>& pixMap) {
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

void NTSC2C02::loadPatternTable() {
  loadPatternTableFromFile(patternTable0, patternTable1);
}


void NTSC2C02::mapMemoryToTables() {
  PPUAddressMappingFunction* ppuAddressMappingFunction = new PPUAddressMappingFunction(this);
  memory->mapAddressRange(0x0000, 0x2FFF, ppuAddressMappingFunction);
}
void NTSC2C02::mapMemoryToCPUBus(Memory * mem) {
  CPUToPPUAddressMappingFunction* CPUToPPUMappingFunction = new CPUToPPUAddressMappingFunction(this);
  mem->mapAddressRange(0x2000, 0x2007, CPUToPPUMappingFunction);
}

void NTSC2C02::tick(R6502 * cpu) {
  // https://www.nesdev.org/wiki/PPU_scrolling#Tile_and_attribute_fetching
  uint16_t tileAddress = 0x2000 | (v & 0x0FFF);
  uint16_t attributeAddress = 0x23C0 | (v & 0x0C00) | ((v >> 4) & 0x38) | ((v >> 2) & 0x07);

  if (scanLine == 261) {
    if (scanLineCycle == 0) {
      allowMaskWrites = 0x1;
      PPUSTATUS->setFlags(STATUS_V, 0x0);
      vBlankStatusNotRead = 0x01;
    }
    if (scanLineCycle >= 257 && scanLineCycle <= 320) {
      ppu->OAMADDR->set(0x00);
      // Sprite evaluation
    }
    scanLineCycle++;
    if (scanLineCycle == 339 && frame == 0) {
      scanLine = 0;
      scanLineCycle = 0;
    }
  } else if (scanLine <= 239) {
    if (scanLineCycle == 0) {
      // Do nothing
    } else if (scanLineCycle <= 256) {
      uint16_t scanLinePhaseCycle = scanLineCycle - 1;
      if ((scanLinePhaseCycle) % 8 == 0) {
        // Fetch tile data
        switch ((scanLineCycle / 8) % 4) {
          case 0:
            // Fetch name table byte
            nameTableByte = memory->read(tileAddress);
            break;
          case 1:
            // Fetch attribute table byte
            attributeTableByte = memory->read(attributeAddress);
            break;
          case 2:
            // Fetch low pattern table tile byte
            break;
          case 3:
            // Fetch high pattern table tile byte
            break;
          default:
            break;
        }
      } else {
        // Do nothing
      }
    } else if (scanLineCycle <= 320) {
      // Fetch sprite data
      uint16_t scanLinePhaseCycle = scanLineCycle - 257;
      if ((scanLinePhaseCycle) % 8 == 0) {
        // Fetch tile data
        switch ((scanLineCycle / 8) % 4) {
          case 0:
            // Fetch garbage name table byte
            break;
          case 1:
            // Fetch garbage name table byte
            break;
          case 2:
            // Fetch low pattern table tile byte
            break;
          case 3:
            // Fetch high pattern table tile byte
            break;
          default:
            break;
        }
      }
    } else if (scanLineCycle <= 336) {
      uint16_t scanLinePhaseCycle = scanLineCycle - 321;
      // Idle
    } else if (scanLineCycle <= 340) {
      uint16_t scanLinePhaseCycle = scanLineCycle - 337;
      if ((scanLinePhaseCycle) % 4 == 0) {
        // Fetch tile data
        switch ((scanLineCycle / 4) % 2) {
          case 0:
            // Fetch name table byte (unknown reason)
            break;
          case 1:
            // Fetch name table byte (unknown reason)
            break;
          default:
            break;
        }
      } else {
        // Do nothing
      }
    }

    if (scanLineCycle < 340) {
      scanLineCycle++;
    } else {
      scanLineCycle = 0;
      scanLine++;
    }
  } else if (scanLine == 240) {
    // Post render scanline
    scanLineCycle++;
    if (scanLineCycle == 340) {
      scanLineCycle = 0;
      scanLine++;
    }
  } else if (scanLine <= 260) {
    if (scanLineCycle == 1) {
      PPUSTATUS->setFlags(STATUS_V, 0x1);
    }
    if (PPUCTRL->getFlag(CTRL_V) && vBlankStatusNotRead) {
      cpu->nmiPending = 0x01;
      vBlankStatusNotRead = 0x00;
    }
    scanLineCycle++;
    if (scanLineCycle == 340) {
      scanLineCycle = 0;
      scanLine++;
      if (scanLine == 261) {
        PPUSTATUS->setFlags(STATUS_V, 0x0);
        frame = (frame + 1) % 2;
      }
    }
  }
}


CPUToPPUAddressMappingFunction::CPUToPPUAddressMappingFunction(NTSC2C02 * ppu) : ppu(ppu), AddressMappingFunction(ppu->memory->ram) {}
uint8_t CPUToPPUAddressMappingFunction::read(uint16_t addr) {
    switch (addr) {
      case 0x2000:
          return ppu->PPUCTRL->get();
      case 0x2001:
          return ppu->PPUMASK->get();
      case 0x2002:
          ppu->OAMDMA->set(0x00); // Reading PPUSTATUS resets OAMDMA
          uint8_t tmp = ppu->PPUSTATUS->get();
          ppu->PPUSTATUS->setFlags(ppu->PPUSTATUS->STATUS_V, 0x0); // Clear VBlank flag
          return tmp;
      case 0x2003:
          return ppu->OAMADDR->get();
      case 0x2004:
          if (ppu->PPUMASK->getFlag(ppu->PPUMASK->MASK_s) || ppu->PPUMASK->getFlag(ppu->PPUMASK->MASK_b)) {
            // rendering is enabled, return open bus
            return 0x00;
          }
          return ppu->OAMDATA->get();
      case 0x2005:
          return ppu->PPUSCROLL->get();
      case 0x2006:
          return ppu->PPUADDR->get();
      case 0x2007:
          if (ppu->PPUMASK->getFlag(ppu->PPUMASK->MASK_s) || ppu->PPUMASK->getFlag(ppu->PPUMASK->MASK_b)) {
            // rendering is enabled, return open bus
            return 0x00;
          }
          if (ppu->PPUCTRL->getFlag(ppu->PPUCTRL->CTRL_I)) {
            ppu->PPUADDR->set(ppu->PPUADDR->get() + 32); // Increment by 32
          } else {
            ppu->PPUADDR->set(ppu->PPUADDR->get() + 1); // Increment by 1
          }
          return ppu->PPUDATA->get();
      default:
          return 0x00;
    }
}
void CPUToPPUAddressMappingFunction::write(uint16_t addr, uint8_t data) {
    switch (addr) {
      case 0x2000:
          ppu->PPUCTRL->set(data);
          ppu->t = (((uint16_t) d & 0x03) << 10) | ppu->t;
          break;
      case 0x2001:
          if (ppu->allowMaskWrites) ppu->PPUMASK->set(data);
          break;
      case 0x2002:
          // status register is read only
          break;
      case 0x2003:
          ppu->OAMADDR->set(data);
          break;
      case 0x2004:
          if (ppu->PPUMASK->getFlag(ppu->PPUMASK->MASK_s) || ppu->PPUMASK->getFlag(ppu->PPUMASK->MASK_b)) {
            // rendering is enabled, do nothing
            break;
          }
          ppu->OAMDATA->set(data);
          memory->write(OAMADDR->get(), data);
          ppu->OAMADDR->set(ppu->OAMADDR->get() + 1); // Increment OAMADDR
          break;
      case 0x2005:
          ppu->PPUSCROLL->set(data);
          if (ppu->w == 0) {
            ppu->t = ((uint16_t) data >> 3) | (ppu->t & 0xFFE0);
            ppu->x = data & 0x07;
            ppu->w = 1;
          } else {
            ppu->t = ((((uint16_t) data) & 0x07) << 12) |
                     ((((uint16_t) data) & 0xF8) << 2) |
                      (ppu->t & 8C1F);

            ppu->w = 0;
          }
          break;
      case 0x2006:
          if (ppu->w == 0) {
            ppu->t = ((uint16_t)(data & 0x3F) << 8) | (ppu->t & 0x00FF);
            ppu->w = 1;
          } else {
            ppu->t = (((uint16_t) data) | (ppu->t & 0x7F00));
            ppu->v = ppu->t;
            ppu->w = 0;
          }
          ppu->PPUADDR->set(data);
          break;
      case 0x2007:
          if (ppu->PPUMASK->getFlag(ppu->PPUMASK->MASK_s) || ppu->PPUMASK->getFlag(ppu->PPUMASK->MASK_b)) {
            // rendering is enabled, do nothing

            // https://www.nesdev.org/wiki/PPU_scrolling#Coarse_X_increment
            if ((ppu->v & 0x001F) == 31) {// if coarse X == 31
              ppu->v &= ~0x001F          // coarse X = 0
              ppu->v ^= 0x0400           // switch horizontal nametable
            } else {
              ppu->v += 1                // increment coarse X
            }

            // https://www.nesdev.org/wiki/PPU_scrolling#Y_increment
            if ((ppu->v & 0x7000) != 0x7000) {       // if fine Y < 7
              ppu->v += 0x1000                      // increment fine Y
            } else {
              ppu->v &= ~0x7000                     // fine Y = 0
              uint16_t y = (ppu->v & 0x03E0) >> 5        // let y = coarse Y
              if (y == 29) {
                y = 0                          // coarse Y = 0
                ppu->v ^= 0x0800                    // switch vertical nametable
              } else if (y == 31) {
                y = 0                          // coarse Y = 0, nametable not switched
              } else {
                y += 1
              }                         // increment coarse Y
              ppu->v = (ppu->v & ~0x03E0) | (y << 5)     // put coarse Y back into v
            }
            break;
          }
          if (ppu->PPUCTRL->getFlag(ppu->PPUCTRL->CTRL_I)) {
            ppu->PPUADDR->set(ppu->PPUADDR->get() + 32); // Increment by 32
          } else {
            ppu->PPUADDR->set(ppu->PPUADDR->get() + 1); // Increment by 1
          }
          ppu->PPUDATA->set(data);
          break;
      default:
          break;
    }
}


PPUAddressMappingFunction::PPUAddressMappingFunction(NTSC2C02 * ppu) : ppu(ppu), AddressMappingFunction(ppu->memory->ram) {}
uint8_t PPUAddressMappingFunction::read(uint16_t addr) {
    if (addr >= 0x0000 && addr <= 0x0FFF) {
        return ppu->patternTable0[addr];
    } else if (addr >= 0x1000 && addr <= 0x1FFF) {
        return ppu->patternTable1[addr - 0x1000];
    } else if (addr >= 0x2000 && addr <= 0x23BF) {
        return ppu->nameTable0[addr - 0x2000];
    } else if (addr >= 0x23C0 && addr <= 0x23FF) {
        return ppu->attributeTable0[addr - 0x23C0];
    } else if (addr >= 0x2400 && addr <= 0x27BF) {
        return ppu->nameTable1[addr - 0x2400];
    } else if (addr >= 0x27C0 && addr <= 0x27FF) {
        return ppu->attributeTable1[addr - 0x27C0];
    } else if (addr >= 0x2800 && addr <= 0x2BBF) {
        return ppu->nameTable0[addr - 0x2800]; // Mirror
    } else if (addr >= 0x2BC0 && addr <= 0x2BFF) {
        return ppu->attributeTable2[addr - 0x2BC0];
    } else if (addr >= 0x2C00 && addr <= 0x2FBF) {
        return ppu->nameTable1[addr - 0x2C00]; // Mirror
    } else if (addr >= 0x2FC0 && addr <= 0x2FFF) {
        return ppu->attributeTable3[addr - 0x2FC0];
    }
    return 0x00;
}
void PPUAddressMappingFunction::write(uint16_t addr, uint8_t data) {
    if (addr >= 0x0000 && addr <= 0x0FFF) {
        ppu->patternTable0[addr] = data;
    } else if (addr >= 0x1000 && addr <= 0x1FFF) {
        ppu->patternTable1[addr - 0x1000] = data;
    } else if (addr >= 0x2000 && addr <= 0x23BF) {
        ppu->nameTable0[addr - 0x2000] = data;
    } else if (addr >= 0x23C0 && addr <= 0x23FF) {
        ppu->attributeTable0[addr - 0x23C0] = data;
    } else if (addr >= 0x2400 && addr <= 0x27BF) {
        ppu->nameTable1[addr - 0x2400] = data;
    } else if (addr >= 0x27C0 && addr <= 0x27FF) {
        ppu->attributeTable1[addr - 0x27C0] = data;
    } else if (addr >= 0x2800 && addr <= 0x2BBF) {
        ppu->nameTable0[addr - 0x2800] = data; // Mirror
    } else if (addr >= 0x2BC0 && addr <= 0x2BFF) {
        ppu->attributeTable2[addr - 0x2BC0] = data;
    } else if (addr >= 0x2C00 && addr <= 0x2FBF) {
        ppu->nameTable1[addr - 0x2C00] = data; // Mirror
    } else if (addr >= 0x2FC0 && addr <= 0x2FFF) {
        ppu->attributeTable3[addr - 0x2FC0] = data;
    }
}