#include "chip8.h"

/**
 * Null OP
 */
void Chip8::OP_NULL() {
    // do nothing
    printf("Instr: NULL OP\n");
}

/**
 * CLS (0x00E0) 
 * Clear the display.
 */
void Chip8::OP_00E0() {
    printf("Instr: CLS\n");

    // set video buffer to zeroes
    memset(video, 0, sizeof(video));
}

/**
 * RET (0x00EE)
 * Return from a subroutine/function.
 */
void Chip8::OP_00EE() {
    printf("Instr: RET\n");
    printf("SP: %d\n", sp);

    sp--;
    pc = stack[sp];
}

/**
 * JUMP (0x1nnn)
 * Jump to the address 0xnnn.
 */
void Chip8::OP_1nnn() {
    printf("Instr: JUMP to 0x%03x\n", opcode & 0x0FFFu);

    uint16_t address = opcode & 0x0FFFu; // last 3 nibbles

    pc = address;
}

/**
 * CALL (0x2nnn)
 * Call the subroutine at adrres 0xnnn.
 */
void Chip8::OP_2nnn() {
    printf("Instr: CALL 0x%03x\n", opcode & 0x0FFFu);

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
    uint8_t x = (opcode & 0x0F00u) >> 8u; // get reg index
    uint8_t byte = opcode & 0x00FFu; // get byte kk

    printf("Instr: SE if V%01x == 0x%02x\n", x, byte);

    if (registers[x] == byte) {
        pc += 2; // skip instruction
    }
}

/**
 * SNE (0x4xkk)
 * Skip next instruction if Vx != kk.
 */
void Chip8::OP_4xkk() {
    uint8_t x = (opcode & 0x0F00u) >> 8u; // get reg index
    uint8_t byte = opcode & 0x00FFu;

    printf("Instr: SNE if V%01x != 0x%02x\n", x, byte);

    if (registers[x] != byte) {
        pc += 2;
    }
}

/** 
 * SE (0x5xy0)
 * Skip next instruction if Vx == Vy.
 */
void Chip8::OP_5xy0() {
    uint8_t x = (opcode & 0x0F00u) >> 8u; // Vx index
    uint8_t y = (opcode & 0x00F0u) >> 4u; // Vy index

    printf("Instr: SE if V%01x == V%01x\n", x, y);

    if (registers[x] == registers[y]) {
        pc += 2;
    }
}

/**
 * LD Vx, byte (0x6xkk)
 * Load byte kk into register x.
 */
void Chip8::OP_6xkk() {
    uint8_t x = (opcode & 0x0F00u) >> 8u; // get reg index
    uint8_t byte = (opcode & 0x00FFu);

    printf("Instr: LD V%01x, 0x%02x\n", x, byte);

    registers[x] = byte;
}

/**
 * ADD Vx, byte (0x7xkk)
 * Add byte to Vx.
 */
void Chip8::OP_7xkk() {
    uint8_t x = (opcode & 0x0F00u) >> 8u; // get reg index
    uint8_t byte = opcode & 0x00FFu; // get byte

    printf("Instr: ADD V%01x, 0x%02x\n", x, byte);

    registers[x] += byte;
}

/**
 * LD Vx, Vy
 * Set Vx = Vy.
 */
void Chip8::OP_8xy0() {
    uint8_t x = (opcode & 0x0F00u) >> 8u;
    uint8_t y = (opcode & 0x00F0u) >> 4u;

    printf("Instr: LD V%01x, V%01x\n", x, y);

    registers[x] = registers[y];
}

/**
 * OR Vx, Vy
 * Set Vx |= Vy
 */
void Chip8::OP_8xy1() {
    uint8_t x = (opcode & 0x0F00u) >> 8u;
    uint8_t y = (opcode & 0x00F0u) >> 4u;

    printf("Instr: OR V%01x, V%01x\n", x, y);

    registers[x] |= registers[y];
}

/**
 * AND Vx, Vy
 * Set Vx &= Vy
 */
void Chip8::OP_8xy2() {
    uint8_t x = (opcode & 0x0F00u) >> 8u;
    uint8_t y = (opcode & 0x00F0u) >> 4u;

    printf("Instr: AND V%01x, V%01x\n", x, y);

    registers[x] &= registers[y];
}

/**
 * XOR Vx, Vy
 * Set Vx |= Vy
 */
void Chip8::OP_8xy3() {
    uint8_t x = (opcode & 0x0F00u) >> 8u;
    uint8_t y = (opcode & 0x00F0u) >> 4u;

    printf("Instr: XOR V%01x, V%01x\n", x, y);

    registers[x] ^= registers[y];
}

/**
 * ADD Vx, Vy
 * Set Vx = Vx + Vy
 * Set Vf = carry
 */
void Chip8::OP_8xy4() {
    uint8_t x = (opcode & 0x0F00u) >> 8u;
    uint8_t y = (opcode & 0x00F0u) >> 4u;

    printf("Instr: ADD V%01x, V%01x\n", x, y);

    uint16_t sum = registers[x] + registers[y];

    registers[0xF] = sum > 255u ? 1 : 0;

    registers[x] = sum & 0xFFu;
}

/**
 * SUB Vx, Vy
 * Set Vx = Vx - Vy
 * Set = NOT borrow
 */
void Chip8::OP_8xy5() {
    uint8_t x = (opcode & 0x0F00u) >> 8u;
    uint8_t y = (opcode & 0X00F0u) >> 4u;

    printf("Instr: SUB V%01x, V%01x\n", x, y);

    registers[0xF] = registers[x] > registers[y] ? 1 : 0;

    registers[x] -= registers[y];
}

/**
 * SHR Vx
 * Set Vx = Vx SHR 1
 * Set Vf if least sig bit is 1
 */
void Chip8::OP_8xy6() {
    uint8_t x = (opcode & 0x0F00u) >> 8u;

    printf("Instr: SHR V%01x\n", x);

    // save least sig bit in VF
    registers[0xF] = (registers[x] & 0x1u);

    registers[x] >>= 1;
}

/**
 * SUBN Vx, Vy
 * Set Vx = Vy - Vx
 * Set Vf = NOT borrow
 */
void Chip8::OP_8xy7() {
    uint8_t x = (opcode & 0x0F00u) >> 8u;
    uint8_t y = (opcode & 0x00F0u) >> 4u;

    printf("Instr: SUBN V%01x, V%01x\n", x, y);

    registers[0xF] = registers[y] > registers[x] ? 1 : 0;

    registers[x] = registers[y] - registers[x];
}

/**
 * SHL Vx {, Vy}
 * Set Vx = Vx SHL 1
 * Set Vf = LSB of Vx
 */
void Chip8::OP_8xyE() {
    uint8_t x = (opcode & 0x0F00u) >> 8u;

    printf("Instr: SHL V%01x\n", x);

    registers[0xF] = (registers[x] & 0x80u) >> 7u;

    registers[x] <<= 1;
}

/**
 * SNE Vx, Vy (0x9xy0)
 * Skip next instruction if Vx != Vy
 */
void Chip8::OP_9xy0() {
    uint8_t x = (opcode & 0x0F00u) >> 8u;
    uint8_t y = (opcode & 0x00F0u) >> 4u;

    printf("Instr: SNE V%01x, V%01x\n", x, y);

    if (registers[x] != registers[y]) {
        pc += 2;
    }
}

/**
 * LD I, addr
 * Set I = addr. (index register)
 */
void Chip8::OP_Annn() {
    uint16_t address = opcode & 0x0FFFu;

    printf("Instr: LD I, 0x%03x\n", address);

    index = address;
}

/**
 * JP V0, addr
 * Jump to address nnn + V0
 */
void Chip8::OP_Bnnn() {
    uint16_t address = opcode & 0x0FFFu;

    printf("Instr: JUMP V0, 0x%03x\n", address);

    pc = registers[0] + address;
}

/**
 * RND Vx, byte
 * Set Vx = random byte AND kk
 */
void Chip8::OP_Cxkk() {
    uint8_t x = (opcode & 0x0F00) >> 8u;
    uint8_t byte = opcode & 0x00FFu;

    printf("Instr: RND V%01x, 0x%02x\n", x, byte);

    registers[x] = randByte(randGen) & byte;
}

/**
 * DRW Vx, Vy, nibble (0xDxyn)
 * Display n-byte sprite starting at memory location I at (Vx, Vy).
 * Set set Vf = collision.
 */
void Chip8::OP_Dxyn() {
    uint8_t x = (opcode & 0x0F00u) >> 8u; // get reg index
    uint8_t y = (opcode & 0x00F0u) >> 4u; // get reg index
    uint8_t height = opcode & 0x000Fu;

    printf("Instr: DRW V%01x, V%01x, 0x%01x\n", x, y, height);

    // wrap beyond screen boundaries
    uint8_t xPos = registers[x] % VIDEO_WIDTH;
    uint8_t yPos = registers[y] % VIDEO_HEIGHT;

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

/**
 * SKP Vx
 * Skip the next instruction if the key with value stored in Vx is pressed.
 */
void Chip8::OP_Ex9E() {
    uint8_t x = (opcode & 0x0F00u) >> 8u;
    uint8_t key = registers[x];

    printf("Instr: SKP V%01x\n", x);

    if (keypad[key]) {
        pc += 2;
    }
}

/**
 * SKNP Vx
 * Skip the next instruction if the key with value stored in Vx is not pressed.
 */
void Chip8::OP_ExA1() {
    uint8_t x = (opcode & 0x0F00u) >> 8u;
    uint8_t key = registers[x];

    printf("Instr: SKNP V%01x\n", x);

    if (!keypad[key]) {
        pc += 2;
    }
}

/**
 * LD Vx, DT
 * Set Vx = delay timer value.
 */
void Chip8::OP_Fx07() {
    uint8_t x = (opcode & 0x0F00u) >> 8u;

    printf("Instr: LD V%01x, DT\n", x);

    registers[x] = delayTimer;
}

/** 
 * LD Vx, K
 * Wait for a key press
 * Store the key value in Vx.
 */
void Chip8::OP_Fx0A() {
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;

	if (keypad[0]) { registers[Vx] = 0; }
	else if (keypad[1]) { registers[Vx] = 1; }
	else if (keypad[2]) { registers[Vx] = 2; }
	else if (keypad[3]) { registers[Vx] = 3; }
	else if (keypad[4]) { registers[Vx] = 4; }
	else if (keypad[5]) { registers[Vx] = 5; }
	else if (keypad[6]) { registers[Vx] = 6; }
	else if (keypad[7]) { registers[Vx] = 7; }
	else if (keypad[8]) { registers[Vx] = 8; }
	else if (keypad[9]) { registers[Vx] = 9; }
	else if (keypad[10]) { registers[Vx] = 10; }
	else if (keypad[11]) { registers[Vx] = 11; }
	else if (keypad[12]) { registers[Vx] = 12; }
	else if (keypad[13]) { registers[Vx] = 13; }
	else if (keypad[14]) { registers[Vx] = 14; }
	else if (keypad[15]) { registers[Vx] = 15; }
	else {
		pc -= 2;
	}

}

/**
 * LD DT, Vx
 * Set delay timer = Vx
 */
void Chip8::OP_Fx15() {
    uint8_t x = (opcode & 0x0F00u) >> 8u;

    printf("Instr: LD DT, V%01x\n", x);

    delayTimer = registers[x];
}

/**
 * LD ST, Vx
 * Set sound timer = Vx
 */
void Chip8::OP_Fx18() {
    uint8_t x = (opcode & 0x0F00u) >> 8u;

    printf("Instr: LD ST, V%01x\n", x);

    soundTimer = registers[x];
}

/**
 * ADD I, Vx
 * Set I = I + Vx
 */
void Chip8::OP_Fx1E() {
    uint8_t x = (opcode & 0x0F00u) >> 8u;

    printf("Instr: I, V%01x\n", x);

    index += registers[x];
}

/**
 * LD F, Vx
 * Set I = location of sprite for digit Vx
 */
void Chip8::OP_Fx29() {
    uint8_t x = (opcode & 0x0F00u) >> 8u;
    
    printf("Instr: LD F, V%01x\n", x);

    uint8_t digit = registers[x];

    index = FONTSET_START_ADDRESS + (digit * FONT_SIZE);
}

/**
 * LD B, Vx
 * Store BCD (binary coded decimal) representation of Vx in memory
 * locations I, I+1 and I+2.
 */
void Chip8::OP_Fx33() {
    uint8_t x = (opcode & 0x0F00u) >> 8u;

    printf("Instr: LD B, V%01x\n", x);

    uint8_t value = registers[x];

    // Ones
    memory[index + 2] = value % 10;
    value /= 10;

    // Tens
    memory[index + 1] = value % 10;
    value /= 10;

    // Hundreds
    memory[index] = value % 10;
}

/**
 * LD [I], Vx
 * Store registers V0 to Vx in memory, starting at location I.
 */
void Chip8::OP_Fx55() {
    uint8_t x = (opcode & 0x0F00u) >> 8u;

    printf("Instr: LD [I], V%01x\n", x);                   

    for (uint8_t i = 0; i <= x; i++) {
        memory[index + i] = registers[i];
    }
}

/**
 * LD Vx [I]
 * Read (load) registers V0 to Vx from memory starting at location I.
 */
void Chip8::OP_Fx65() {
    uint8_t x = (opcode & 0x0F00u) >> 8u;

    printf("Instr: LD V%01x, [I]\n", x);

    for (uint8_t i = 0; i <= x; i++) {
        registers[i] = memory[index + i];
    }
}