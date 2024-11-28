#include "chip8.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>

const unsigned int START_ADDRESS = 0x200;

Chip8::Chip8() {

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