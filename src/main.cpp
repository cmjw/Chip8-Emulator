#include "chip8.h"

int main(int argc, char* argv[]) {
    // print signs of life
    printf("||||||||||||||||\n");
    printf("Chip8 Emulator\n");
    printf("||||||||||||||||\n");

    Chip8 chip8;
    const char* ROMfilename = "../roms/test.ch8";

    chip8.LoadROM(ROMfilename);

    chip8.MemoryDump();

    printf("Quit\n");
    return 0;
}