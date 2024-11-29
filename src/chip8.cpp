#include "chip8.h"

uint8_t fontset[FONTSET_SIZE] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};
/* Chip8 supports a keypad with characters 0 to F.
    Each is displayed in a 8x5 pixel image, which can 
    be represented by 5 bytes.*/


Chip8::Chip8() : randGen(std::chrono::system_clock::now().time_since_epoch().count()) {
    // initialize pc
    pc = START_ADDRESS;

    // load fonts into memory
    for (unsigned int i = 0; i < FONTSET_SIZE; i++) {
        memory[FONTSET_START_ADDRESS + i] = fontset[i];
    }

    // initialize random number generator
    randByte = std::uniform_int_distribution<uint8_t>(0, 255U);
}

Chip8::~Chip8() {

}

/**
 * Load a ROM into memory.
 * The contents are loaded starting at 0x200 in memory.
 */
void Chip8::LoadROM(const char* filename) {
    // open file stream
    // ios::ate places cursor at endfile after opening
    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if (file.is_open()) {
        // get size and allocate buffer
        std::streampos size = file.tellg(); 
        char* buffer = new char[size];

        // move cursor to beginning of file
        file.seekg(0, std::ios::beg);
        
        // fill buffer
        file.read(buffer, size);
        file.close();

        // load ROM contents into memory, starting at 0x200
        for (long i = 0; i < size; i++) {
            memory[START_ADDRESS + i] = buffer[i];
        }

        // free the buffer
        delete[] buffer;
    }    
}

/**
 * Print memory contents.
 */
void Chip8::MemoryDump() {
    int j = 0;
    for (int i = 0; i < 4096; i++) {
        if (j % 8 == 0) {
            printf("\n");
        }
        printf("%02x ", memory[i]);
        j++;
    }
}