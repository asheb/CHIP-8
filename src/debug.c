#include <stdio.h>
#include "debug.h"
#include "machine.h"


void print_memory(chip8_machine const* machine, size_t bytes_per_line, size_t starting_address, size_t bytes_to_print) {
    for (size_t i = starting_address; i < BYTES_IN_MEMORY && i < starting_address + bytes_to_print; i++) {
        if (i % bytes_per_line == 0) {
            if (i) putchar('\n');
            printf("%03zx: ", i);
        }
        printf("%02x ", machine->memory[i]);
    }
    putchar('\n');
}


void print_registers(chip8_machine const* machine) {
    for (size_t i = 0; i < DATA_REGISTERS_COUNT; i++)
        printf("V%zX=%02x ", i, machine->data_registers_Vx[i]);
    printf("I=%03x PC=%03x\n", machine->address_register_I, machine->instruction_pointer);
}

