#ifndef CHIP8_H
#define CHIP8_H

#include <cstdint>
#include <random>
#include <SDL2/SDL.h>

const unsigned int START_ADDRESS = 0x200;
const unsigned int FONTSET_START_ADDRESS = 0x50;

const unsigned int FONTSET_SIZE = 80;

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
    
    uint16_t pc; // 16-bit program counter

    uint8_t sp; // 8-bit stack pointer

    uint16_t stack[16]; // 16 level stack (16 bit)

    uint16_t opcode; // current opcode

    uint8_t delayTimer;
    uint8_t soundTimer;

    uint8_t keypad[16]; // 16 character keypad

    uint32_t video[64 * 32]; // 64x32 video output
    /* monochrome video. each 32-bit pixel is on or off.*/

    std::default_random_engine randGen;
	std::uniform_int_distribution<uint8_t> randByte;

    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
};

#endif