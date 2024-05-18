#include <stdio.h>
#include "debug.h"
#include "machine.h"


void print_memory(chip8_machine* machine, size_t bytes_per_line) {
    for (size_t i = 0; i < BYTES_IN_MEMORY; i++) {
        if (i % bytes_per_line == 0) {
            if (i) putchar('\n');
            printf("%03zx: ", i);
        }
        printf("%02x ", machine->memory[i]);
    }
    putchar('\n');
}


void print_registers(chip8_machine* machine) {
    for (size_t i = 0; i < DATA_REGISTERS_COUNT; i++)
        printf("V%zu=%u ", i, machine->data_registers_Vx[i]);
    printf("I=%03xh PC=%03xh\n", machine->address_register_I, machine->instruction_pointer);
}

