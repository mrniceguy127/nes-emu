#include <iostream>

#include <SDL3/SDL.h>

#include "NTSC2C02.h"

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
  memory->mapAddressRange(0x0000, 0x0FFF, reinterpret_cast<uint64_t>(patternTable0.data()));
  memory->mapAddressRange(0x1000, 0x1FFF, reinterpret_cast<uint64_t>(patternTable1.data()));
  memory->mapAddressRange(0x2000, 0x23BF, reinterpret_cast<uint64_t>(nameTable0.data()));
  memory->mapAddressRange(0x23C0, 0x23FF, reinterpret_cast<uint64_t>(attributeTable0.data()));
  memory->mapAddressRange(0x2400, 0x27BF, reinterpret_cast<uint64_t>(nameTable1.data()));
  memory->mapAddressRange(0x27C0, 0x27FF, reinterpret_cast<uint64_t>(attributeTable1.data()));
  memory->mapAddressRange(0x2800, 0x2BBF, reinterpret_cast<uint64_t>(nameTable0.data())); // Mirror
  memory->mapAddressRange(0x2BC0, 0x2BFF, reinterpret_cast<uint64_t>(attributeTable2.data()));
  memory->mapAddressRange(0x2C00, 0x2FBF, reinterpret_cast<uint64_t>(nameTable1.data())); // Mirror
  memory->mapAddressRange(0x2FC0, 0x2FFF, reinterpret_cast<uint64_t>(attributeTable3.data()));

}
void NTSC2C02::mapMemoryToCPUBus(Memory * mem) {
  mem->mapAddress(0x2000, reinterpret_cast<uint64_t>(&controlRegister1));
  mem->mapAddress(0x2001, reinterpret_cast<uint64_t>(&controlRegister2));
  mem->mapAddress(0x2002, reinterpret_cast<uint64_t>(&statusRegister));
  mem->mapAddress(0x2003, reinterpret_cast<uint64_t>(&spriteAddress));
  mem->mapAddress(0x2004, reinterpret_cast<uint64_t>(&spriteData));
  mem->mapAddress(0x2005, reinterpret_cast<uint64_t>(&scroll));
  mem->mapAddress(0x2006, reinterpret_cast<uint64_t>(&address));
  mem->mapAddress(0x2007, reinterpret_cast<uint64_t>(&data));
}

void NTSC2C02::tick() {
  if (scanLineCycle == 0) {
    // Do nothing
  } else if (scanLineCycle <= 256) {
    uint16_t scanLinePhaseCycle = scanLineCycle - 1;
    if ((scanLinePhaseCycle) % 8 == 0) {
      // Fetch tile data
      switch ((scanLineCycle / 8) % 4) {
        case 0:
          // Fetch name table byte
          break;
        case 1:
          // Fetch attribute table byte
          break;
        case 2:
          // Fetch low tile byte
          break;
        case 3:
          // Fetch high tile byte
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
          // Fetch low tile byte
          break;
        case 3:
          // Fetch high tile byte
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
      }
    } else {
      // Do nothing
    }
  }

  if (scanLineCycle < 340) {
    scanLineCycle++;
  } else {
    scanLineCycle = 0;
  }
}