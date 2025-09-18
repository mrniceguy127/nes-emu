#include "NESIncludes.h"
#include "Debugger.h"
#include <SDL3/SDL.h>
#include <iostream>
#include <fstream>
#include <iomanip>

void debug(R6502 * cpu);


static bool is_nes2(uint8_t f7) { return (f7 & 0x0C) == 0x08; }

bool loadFromFile(const std::string& path, NTSC2C02* ppu, R6502* cpu) {
  std::ifstream file(path, std::ios::binary);
  if (!file) { std::cerr << "Failed to open: " << path << "\n"; return false; }

  uint8_t h[16] = {0};
  file.read(reinterpret_cast<char*>(h), 16);
  if (file.gcount() != 16 || h[0] != 'N' || h[1] != 'E' || h[2] != 'S' || h[3] != 0x1A) {
    std::cerr << "Not an iNES file (bad magic)\n"; return false;
  }

  const uint8_t prgBanks = h[4];               // 16KB units
  const uint8_t chrBanks = h[5];               // 8KB units (0 => CHR-RAM)
  const uint8_t flags6  = h[6];
  const uint8_t flags7  = h[7];

  // Mapper (only support 0 here)
  const uint16_t mapper = (flags6 >> 4) | (flags7 & 0xF0);
  if (is_nes2(flags7)) {
    std::cerr << "NES 2.0 ROMs not supported in this minimal loader\n";
    return false;
  }
  if (mapper != 0) {
    std::cerr << "Mapper " << mapper << " not supported by this loader (expect 0/NROM)\n";
    return false;
  }

  const bool hasTrainer = (flags6 & 0x04) != 0;
  // const bool mirroringVertical = (flags6 & 0x01) != 0; // (keep for later)
  // const bool fourScreen = (flags6 & 0x08) != 0;

  // Seek past optional trainer
  if (hasTrainer) { file.seekg(512, std::ios::cur); }

  // ---- Load PRG ROM ----
  if (prgBanks == 0 || prgBanks > 2) {
    std::cerr << "PRG banks " << int(prgBanks) << " unsupported in NROM-only loader\n";
    return false;
  }

  const size_t PRG16K = 16 * 1024;
  std::vector<uint8_t> prg(prgBanks * PRG16K);
  file.read(reinterpret_cast<char*>(prg.data()), prg.size());
  if (size_t(file.gcount()) != prg.size()) { std::cerr << "Short read on PRG\n"; return false; }

  // Map into CPU space
  // NROM mapping: $8000-$BFFF and $C000-$FFFF
  // If only 16KB, mirror it into both halves.
  if (prgBanks == 1) {
    std::copy(prg.begin(), prg.begin() + PRG16K, cpu->memory->ram.begin() + 0x8000);
    std::copy(prg.begin(), prg.begin() + PRG16K, cpu->memory->ram.begin() + 0xC000);
    std::cout << "Mirroring 16KB PRG ROM\n";
  } else { // prgBanks == 2
    std::copy(prg.begin(),                 prg.begin() + PRG16K, cpu->memory->ram.begin() + 0x8000);
    std::copy(prg.begin() + PRG16K,        prg.end(),            cpu->memory->ram.begin() + 0xC000);
  }

  // ---- Load CHR (8KB) or init CHR-RAM ----
  const size_t CHR8K = 8 * 1024;
  if (chrBanks == 0) {
    // CHR-RAM (8KB): clear it; games will fill via $2007
    std::fill(ppu->patternTable0.begin(), ppu->patternTable0.end(), 0);
    std::fill(ppu->patternTable1.begin(), ppu->patternTable1.end(), 0);
  } else {
    // Read only the first 8KB into the two 4KB pattern tables
    std::vector<uint8_t> chr(std::min<size_t>(chrBanks * CHR8K, CHR8K));
    file.read(reinterpret_cast<char*>(chr.data()), chr.size());
    if (size_t(file.gcount()) != chr.size()) { std::cerr << "Short read on CHR\n"; return false; }
    std::copy(chr.begin(),                  chr.begin() + 0x1000, ppu->patternTable0.begin());
    std::copy(chr.begin() + 0x1000,         chr.begin() + 0x2000, ppu->patternTable1.begin());
  }

  // Optional: dump header info
  std::cout << "iNES: PRG=" << int(prgBanks) << "x16KB, CHR=" << int(chrBanks)
            << "x8KB, mapper=" << mapper
            << (hasTrainer ? ", trainer" : "")
            << "\n";

  return true;
}

int main() {
  Memory * cpuMemory = new Memory();
  R6502 cpu = R6502(cpuMemory);
  Memory * ppuMemory = new Memory();
  NTSC2C02 ppu = NTSC2C02(ppuMemory);
  ppu.mapMemoryToCPUBus(cpuMemory);
  loadFromFile("./src/full_nes_palette.nes", &ppu, &cpu);
  cpu.powerOn();
  ConsoleDebugger dbg(&cpu);

  //return 0;
  //while (true) {
  //}
  //debug(&cpu);

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window * window = SDL_CreateWindow("Pattern Table", 1024, 960, SDL_WINDOW_RESIZABLE);
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
  int height = 0xF0;
  SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
  if (texture == nullptr) {
      std::cerr << "SDL_CreateTexture Error: " << SDL_GetError() << "\n";
      SDL_DestroyRenderer(renderer);
      SDL_DestroyWindow(window);
      SDL_Quit();
      return 1;
  }
  // 3. Lock the Texture to Access Pixels
  /*void* pixels;
  int pitch;
  if (!SDL_LockTexture(texture, NULL, &pixels, &pitch)) {
      std::cerr << "SDL_LockTexture Error: " << SDL_GetError() << "\n";
      SDL_DestroyTexture(texture);
      SDL_DestroyRenderer(renderer);
      SDL_DestroyWindow(window);
      SDL_Quit();
      return 1;
  }*/

  // 4. Main event loop
  bool running = true;
  SDL_Event event;
  uint8_t phase = 0;
  while (running) {
    switch(phase) {
      case 0:
        cpu.tick();
        //dbg.showState();
        //SDL_Delay(50);
        //std::cout << "cpu1" << std::endl;
        //std::cout << "ppu 2002: " << std::hex << int(ppu.PPUSTATUS->get()) << std::dec << std::endl;
        //std::cout << "cpu 2002: " << std::hex << int(cpu.memory->read(0x2002)) << std::dec << std::endl;
        phase++;
        break;
      case 1:
        ppu.tick(&cpu);
        //std::cout << "ppu1" << std::endl;
        phase++;
        break;
      case 2:
        ppu.tick(&cpu);
        //std::cout << "ppu2" << std::endl;
        phase++;
        break;
      case 3:
        ppu.tick(&cpu);
        //std::cout << "ppu3" << std::endl;
        phase = 0;
        break;
      default:
        break;
    }

    if (!ppu.frameComplete) {
      continue;
    } else {
      SDL_Delay(16);
    }

    void* pixels = nullptr;
    int pitch = 0;
    if (SDL_LockTexture(texture, nullptr, &pixels, &pitch) == 0) {
      std::cerr << "SDL_LockTexture Error: " << SDL_GetError() << "\n";
      running = false;
      break;
    }

    // 4. Modify Pixel Data
    // We'll create a simple gradient
    std::array<Color, 0x100 * 0xF0> * screen = &ppu.pixMap;
    uint32_t * pixel_ptr = static_cast<uint32_t*>(pixels);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            uint16_t location = calcLocation(x, y, 0x100);
            Color color = (*screen)[location];
            uint32_t r = color.r;
            uint32_t g = color.g;
            uint32_t b = color.b;
            uint32_t pixel_color = (r << 16) | (g << 8) | b | 0xFF000000;
            pixel_ptr[(y * 0x100) + x] = pixel_color;
        }
    }

    // 5. Unlock the Texture
    SDL_UnlockTexture(texture);
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
  }

  // 5. Clean up and quit SDL
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void debug(R6502 * cpu) {
  ConsoleDebugger debugger = ConsoleDebugger(cpu);
  int i = 0;
  while (i < 10) {
    debugger.step();
    i++;
  }
}

