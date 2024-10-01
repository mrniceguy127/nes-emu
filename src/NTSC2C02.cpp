#include <iostream>

#include <SDL2/SDL.h>

#include "NTSC2C02.h"

int main() {
  std::array<Color, 0x100 * 0x80> screen;
  NTSC2C02 ppu = NTSC2C02();
  ppu.generatePixMap(screen);
  
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window * window = SDL_CreateWindow("Pattern Table", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 512, SDL_WINDOW_SHOWN);
  if (window == nullptr) {
      std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
      return 1;
  } else {
      std::cout << "SDL_CreateWindow Success" << std::endl;
  }
  SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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
    if (SDL_LockTexture(texture, NULL, &pixels, &pitch) != 0) {
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
            if (event.type == SDL_QUIT) {  // User requests quit
                running = false;
            }
        }

        // Clear the screen with a color (e.g., Cornflower Blue)
        SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255); // RGBA
        SDL_RenderClear(renderer);

        // Render the Texture
        SDL_RenderCopy(renderer, texture, NULL, NULL);

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