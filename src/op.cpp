#include "chip8.h"

/*
 * CLS (0x00E0) 
 * Clear the display.
 */
void Chip8::OP_00E0() {
    // set video buffer to zeroes
    memset(video, 0, sizeof(video));
}