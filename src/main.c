#include <stdio.h>
#include <stdlib.h>
#include "machine.h"
#include "loader.h"
#include "debug.h"


int main(int argc, char const* argv[]) {
    if (argc != 2) {
        puts("usage: chip8 <filename>");
        return EXIT_FAILURE;
    }

    chip8_machine machine = { 0 };

    load_rom(&machine, argv[1]);


    print_memory(&machine, 32);







    return EXIT_SUCCESS;
}


