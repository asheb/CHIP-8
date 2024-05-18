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

    print_memory(&machine, 32, PROGRAM_BASE_ADDRESS, 0x200);
    print_registers(&machine);

    for (;;) {
        putchar('\n');
        process_current_instruction(&machine);
        print_registers(&machine);
    }


    //return EXIT_SUCCESS;
}


