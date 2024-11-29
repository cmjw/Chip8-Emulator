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

void Chip8::OP_1nnn() {

}

void Chip8::OP_2nnn() {

}

void Chip8::OP_3xkk() {

}

void Chip8::OP_4xkk() {

}

void Chip8::OP_5xy0() {

}

void Chip8::OP_6xkk() {

}

void Chip8::OP_7xkk() {

}

void Chip8::OP_8xy0() {

}

void Chip8::OP_8xy1() {

}

void Chip8::OP_8xy2() {

}

void Chip8::OP_8xy3() {

}

void Chip8::OP_8xy4() {

}

void Chip8::OP_8xy5() {

}

void Chip8::OP_8xy6() {

}

void Chip8::OP_8xy7() {

}

void Chip8::OP_8xyE() {

}

void Chip8::OP_9xy0() {

}

void Chip8::OP_Annn() {

}

void Chip8::OP_Bnnn() {

}

void Chip8::OP_Cxkk() {

}

void Chip8::OP_Dxyn() {

}

void Chip8::OP_Ex9E() {

}

void Chip8::OP_ExA1() {

}

void Chip8::OP_Fx07() {

}

void Chip8::OP_Fx0A() {

}

void Chip8::OP_Fx15() {

}

void Chip8::OP_Fx18() {

}

void Chip8::OP_Fx1E() {

}

void Chip8::OP_Fx29() {

}

void Chip8::OP_Fx33() {

}

void Chip8::OP_Fx55() {

}

void Chip8::OP_Fx65() {
    
}