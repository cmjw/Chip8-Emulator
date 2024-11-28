#include "chip8.h"

int main(int argc, char* argv[]) {
    Chip8 chip8;
    const char* ROMfilename = "../roms/test.ch8";

    chip8.LoadROM(ROMfilename);
    return 0;
}