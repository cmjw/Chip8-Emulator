#ifndef CHIP8_H
#define CHIP8_H

#include <cstdint>
#include <SDL2/SDL.h>

const int DISPLAY_WIDTH = 64;
const int DISPLAY_HEIGHT = 32;
const int PIXEL_SCALE = 10; 

class Chip8 {
public:
    Chip8();
    ~Chip8();

    uint8_t memory[4096]; // 4096 bytes of memory
    /* - 0x200 to 0xFFF is program space
       - 0x000 to 0x1FF is reserved
           - 0x050 to 0x0A0 stores 16 built-in chars */

    uint8_t registers[16]; // 16 8-bit registers
    /* V0 to VF, 0x00 to 0xFF
        VF is used as a flag */

    uint16_t index; // special 16-bit index register
    /* stores an address. needed because 8-bit registers can't store
        largest location. 
        usually only uses lower 12 bits. (2^12 = 4096)*/

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