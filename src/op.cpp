#include "chip8.h"

/**
 * Null OP
 */
void Chip8::OP_NULL() {
    
}

/**
 * CLS (0x00E0) 
 * Clear the display.
 */
void Chip8::OP_00E0() {
    // set video buffer to zeroes
    memset(video, 0, sizeof(video));
}

/**
 * RET (0x00EE)
 * Return from a subroutine/function.
 */
void Chip8::OP_00EE() {
    sp--;
    pc = stack[pc];
}