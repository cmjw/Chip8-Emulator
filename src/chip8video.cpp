#include "chip8video.h"

Chip8_Video::Chip8_Video(int windowWidth, int windowHeight, int textureWidth, int textureHeight) {
    // initialize SDL video
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Chip-8 Emulator", 0, 0, windowWidth, windowHeight, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, textureWidth, textureHeight);
}

Chip8_Video::~Chip8_Video() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}