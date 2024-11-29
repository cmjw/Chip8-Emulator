#include "chip8.h"
#include "chip8video.h"

int main(int argc, char* argv[]) {
    // print signs of life
    printf("||||||||||||||||\n");
    printf("Chip8 Emulator\n");
    printf("||||||||||||||||\n\n");

    Chip8 chip8;
    const char* ROMfilename = "../roms/test.ch8";

    chip8.LoadROM(ROMfilename);

    chip8.MemoryDump();

    printf("Quit\n");
    return 0;
}