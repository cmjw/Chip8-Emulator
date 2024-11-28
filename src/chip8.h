#ifndef CHIP8_H
#define CHIP8_H

#include <SDL2/SDL.h>

const int DISPLAY_WIDTH = 64;
const int DISPLAY_HEIGHT = 32;
const int PIXEL_SCALE = 10; 

class Chip8 {
public:
    Chip8();
    ~Chip8();

    void LoadROM(const char* filename);

    // void Run();         
    // void Render();
    // void HandleInput();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
};

#endif