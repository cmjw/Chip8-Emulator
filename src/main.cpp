#include "chip8.h"
#include "chip8video.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    // print signs of life
    printf("||||||||||||||||\n");
    printf(" Chip8 Emulator\n");
    printf("||||||||||||||||\n\n");

    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <Scale> <Delay> <ROM>\n";
        return -1;
    }

    // cmd args
    int videoScale = std::stoi(argv[1]);
    int cycleDelay = std::stoi(argv[2]);
    char const* ROMfilename = argv[3];

    Chip8 chip8;
    chip8.LoadROM(ROMfilename);

    chip8.MemoryDump();

    printf("Quit\n");
    return 0;
}