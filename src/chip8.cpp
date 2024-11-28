#include "chip8.h"
#include <SDL2/SDL.h>
#include <iostream>

Chip8::Chip8() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Create the window
    window = SDL_CreateWindow("Chip-8 Emulator",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              DISPLAY_WIDTH * PIXEL_SCALE,
                              DISPLAY_HEIGHT * PIXEL_SCALE,
                              SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Create the renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

Chip8::~Chip8() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
}

void Chip8::Render() {
    SDL_RenderClear(renderer); 
    SDL_RenderPresent(renderer);
}

void Chip8::HandleInput() {
    // placeholder
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            running = false;
        }
    }
}

void Chip8::Run() {
    running = true;
    while (running) {
        HandleInput();
        Render();
        SDL_Delay(16); 
    }
}
