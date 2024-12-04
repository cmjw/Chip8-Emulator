#include "disassembler.h"
#include <stdio.h>

int main (int argc, char* argv[]) {
    // check args
    if (argc < 2) {
        printf("Usage: %s <file to disassemble\n", argv[0]);
    }

    return 0;
}