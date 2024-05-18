#include <stdio.h>
#include "debug.h"
#include "machine.h"


void print_memory(chip8_machine* machine, size_t bytes_per_line) {
    for (size_t i = 0; i < BYTES_IN_MEMORY; i++) {
        if (i % bytes_per_line == 0) {
            if (i) putchar('\n');
            printf("%04zx: ", i);
        }
        printf("%02x ", machine->memory[i]);
    }
    putchar('\n');
}


