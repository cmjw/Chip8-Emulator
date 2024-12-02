#include "chip8.h"

/**
 * Null OP
 */
void Chip8::OP_NULL() {
    // do nothing
}

/**
 * CLS (0x00E0) 
 * Clear the display.
 */
void Chip8::OP_00E0() {
    printf("Instr: CLS 0x00E0\n");

    // set video buffer to zeroes
    memset(video, 0, sizeof(video));
}

/**
 * RET (0x00EE)
 * Return from a subroutine/function.
 */
void Chip8::OP_00EE() {
    printf("Instr: RET (0x00EE)\n");
    printf("SP: %d\n", sp);

    sp--;
    pc = stack[sp];
}

/**
 * JUMP (0x1nnn)
 * Jump to the address 0xnnn.
 */
void Chip8::OP_1nnn() {
    printf("Instr: JUMP to %03x\n", opcode & 0x0FFFu);

    uint16_t address = opcode & 0x0FFFu; // last 3 nibbles

    pc = address;
}

/**
 * CALL (0x2nnn)
 * Call the subroutine at adrres 0xnnn.
 */
void Chip8::OP_2nnn() {
    printf("Instr: CALL %03x\n", opcode & 0x0FFFu);

    uint16_t address = opcode & 0x0FFFu;

    stack[sp] = pc; // put next seq instruction on stack
    sp++;
    printf("SP: %d\n", sp);

    pc = address; // execute subroutine
}

/**
 * SE (0x3xkk)
 * Skip next instruction if Vx == kk.
 */
void Chip8::OP_3xkk() {
    uint8_t Vx = (opcode & 0x0F00u) >> 8u; // get reg index
    uint8_t byte = opcode & 0x00FFu; // get byte kk

    printf("Instr: SE if V%01x == %02x\n", Vx, byte);

    if (registers[Vx] == byte) {
        pc += 2; // skip instruction
    }
}

/**
 * SNE (0x4xkk)
 * Skip next instruction if Vx != kk.
 */
void Chip8::OP_4xkk() {
    uint8_t Vx = (opcode & 0x0F00u) >> 8u; // get reg index
    uint8_t byte = opcode & 0x00FFu;

    printf("Instr: SNE if V%01x != %02x\n", Vx, byte);

    if (registers[Vx] != byte) {
        pc += 2;
    }
}

/** 
 * SE (0x5xy0)
 * Skip next instruction if Vx == Vy.
 */
void Chip8::OP_5xy0() {
    uint8_t Vx = (opcode & 0x0F00u) >> 8u; // Vx index
    uint8_t Vy = (opcode & 0x00F0u) >> 4u; // Vy index

    printf("Instr: SE if V%01x == V%01x\n", Vx, Vy);

    if (registers[Vx] == registers[Vy]) {
        pc += 2;
    }
}

/**
 * LD Vx, byte (0x6xkk)
 * Load byte kk into register x.
 */
void Chip8::OP_6xkk() {
    uint8_t Vx = (opcode & 0x0F00u) >> 8u; // get reg index
    uint8_t byte = (opcode & 0x00FFu);

    printf("Instr: LD V%01x, %02x\n", Vx, byte);

    registers[Vx] = byte;
}

/**
 * ADD Vx, byte (0x7xkk)
 * Add byte to Vx.
 */
void Chip8::OP_7xkk() {
    uint8_t Vx = (opcode & 0x0F00u) >> 8u; // get reg index
    uint8_t byte = opcode & 0x00FFu; // get byte

    printf("Instr: ADD V%01x, %02x\n", Vx, byte);

    registers[Vx] += byte;
}

/**
 * LD Vx, Vy
 * Set Vx = Vy.
 */
void Chip8::OP_8xy0() {
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    printf("Instr: LD V%01x, V%01x\n", Vx, Vy);

    registers[Vx] = registers[Vy];
}

/**
 * OR Vx, Vy
 * Set Vx |= Vy
 */
void Chip8::OP_8xy1() {
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    printf("Instr: OR V%01x, V%01x\n", Vx, Vy);

    registers[Vx] |= registers[Vy];
}

/**
 * AND Vx, Vy
 * Set Vx &= Vy
 */
void Chip8::OP_8xy2() {
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    printf("Instr: AND V%01x, V%01x\n", Vx, Vy);

    registers[Vx] &= registers[Vy];
}

/**
 * XOR Vx, Vy
 * Set Vx |= Vy
 */
void Chip8::OP_8xy3() {
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    printf("Instr: XOR V%01x, V%01x\n", Vx, Vy);

    registers[Vx] ^= registers[Vy];
}

/**
 * ADD Vx, Vy
 * Set Vx = Vx + Vy
 * Set Vf = carry
 */
void Chip8::OP_8xy4() {
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    printf("Instr: ADD V%01x, V%01x\n", Vx, Vy);

    uint16_t sum = registers[Vx] + registers[Vy];

    registers[0xF] = sum > 255u ? 1 : 0;

    registers[Vx] = sum & 0xFFu;
}

/**
 * SUB Vx, Vy
 * Set Vx = Vx - Vy
 * Set = NOT borrow
 */
void Chip8::OP_8xy5() {
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0X00F0u) >> 4u;

    printf("Instr: SUB V%01x, V%01x\n", Vx, Vy);

    registers[0xF] = registers[Vx] > registers[Vy] ? 1 : 0;

    registers[Vx] -= registers[Vy];
}

/**
 * SHR Vx
 * Set Vx = Vx SHR 1
 * Set Vf if least sig bit is 1
 */
void Chip8::OP_8xy6() {
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;

    printf("Instr: SHR V%01x\n", Vx);

    // save least sig bit in VF
    registers[0xF] = (registers[Vx] & 0x1u);

    registers[Vx] >>= 1;
}

/**
 * SUBN Vx, Vy
 * Set Vx = Vy - Vx
 * Set Vf = NOT borrow
 */
void Chip8::OP_8xy7() {
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    printf("Instr: SUBN V%01x, V%01x\n", Vx, Vy);

    registers[0xF] = registers[Vy] > registers[Vx] ? 1 : 0;

    registers[Vx] = registers[Vy] - registers[Vx];
}

/**
 * SHL Vx {, Vy}
 * Set Vx = Vx SHL 1
 * Set Vf = LSB of Vx
 */
void Chip8::OP_8xyE() {
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;

    printf("Instr: SHL V%01x\n", Vx);

    registers[0xF] = (registers[Vx] & 0x80u) >> 7u;

    registers[Vx] <<= 1;
}

/**
 * SNE Vx, Vy (0x9xy0)
 * Skip next instruction if Vx != Vy
 */
void Chip8::OP_9xy0() {
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    printf("Instr: SNE V%01x, V%01x\n", Vx, Vy);

    if (registers[Vx] != registers[Vy]) {
        pc += 2;
    }
}

/**
 * LD I, addr
 * Set I = addr. (index register)
 */
void Chip8::OP_Annn() {
    uint16_t address = opcode & 0x0FFFu;

    printf("Instr: LD I, %03x\n", address);

    index = address;
}

/**
 * JP V0, addr
 * Jump to address nnn + V0
 */
void Chip8::OP_Bnnn() {
    uint16_t address = opcode & 0x0FFFu;

    printf("Instr: JUMP V0, %03x\n", address);

    pc = registers[0] + address;
}

/**
 * RND Vx, byte
 * Set Vx = random byte AND kk
 */
void Chip8::OP_Cxkk() {
    uint8_t Vx = (opcode & 0x0F00) >> 8u;
    uint8_t byte = opcode & 0x00FFu;

    printf("Instr: RND V%01x, %02x\n", Vx, byte);

    registers[Vx] = randByte(randGen) & byte;
}

/**
 * DRW Vx, Vy, nibble (0xDxyn)
 * Display n-byte sprite starting at memory location I at (Vx, Vy).
 * Set set Vf = collision.
 */
void Chip8::OP_Dxyn() {
    uint8_t Vx = (opcode & 0x0F00u) >> 8u; // get reg index
    uint8_t Vy = (opcode & 0x00F0u) >> 4u; // get reg index
    uint8_t height = opcode & 0x000Fu;

    printf("Instr: DRW V%01x, V%01x, %01x\n", Vx, Vy, height);

    // wrap beyond screen boundaries
    uint8_t xPos = registers[Vx] % VIDEO_WIDTH;
    uint8_t yPos = registers[Vy] % VIDEO_HEIGHT;

    registers[0xF] = 0; // set Vf

    for (unsigned int row = 0; row < height; row++) {
        uint8_t spriteByte = memory[index + row];

        for (unsigned int col = 0; col < 8; col++) { // 1 byte
            uint8_t spritePixel = spriteByte & (0x80u >> col);
            uint32_t* screenPixel = &video[(yPos + row) * VIDEO_WIDTH + (xPos + col)];

            if (spritePixel) { // if sprite pixel on
                if (*screenPixel == 0xFFFFFFFF) { // if screen pixel on
                    registers[0xF] = 1; // collision
                }

                // XOR screen pixel with sprite pixel
                *screenPixel ^= 0xFFFFFFFF;
            }
        }
    }
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