#include <stdio.h>
#include "debug.h"
#include "machine.h"
#include "ui.h"


void print_memory(CHIP8_Machine const* machine, size_t bytes_per_line, size_t starting_address, size_t bytes_to_print) {
    for (size_t i = starting_address; i < BYTES_IN_MEMORY && i < starting_address + bytes_to_print; i++) {
        if (i % bytes_per_line == 0) {
            if (i) putchar('\n');
            printf("%03zx: ", i);
        }

        if (i == machine->instruction_pointer) {
            set_color(Color_white);
            set_background_color(Color_dark_gray);
        }

        printf("%02x", machine->memory[i]);

        if (i == machine->instruction_pointer + 1) {
            set_color(Color_default);
            set_background_color(Color_default);
        }

        printf(" ");
    }
    putchar('\n');
}


void print_registers(CHIP8_Machine const* machine) {
    for (size_t i = 0; i < DATA_REGISTERS_COUNT; i++)
        printf("V%zX=%02x ", i, machine->data_registers_Vx[i]);
    printf("I=%03x PC=%03x\n", machine->address_register_I, machine->instruction_pointer);
}


void describe_current_instruction(CHIP8_Machine const* machine) {
    CHIP8_Instruction i = get_current_instruction(machine);
    printf("%04x: ", i.full);

    if (i.full == 0x00e0) printf("Clear the screen");
    else if (i.h ==   6)  printf("Store number %02Xh in register V%X", i.nn, i.x);
    else if (i.h == 0xa)  printf("Store memory address %03Xh in register I", i.nnn);
    else                  printf("-unknown instruction-");
}


void print_screen(CHIP8_Machine const* machine) {
    for (size_t y = 0; y < SCREEN_HEIGHT; y++) {
        for (size_t x = 0; x < SCREEN_WIDTH; x++)
            printf("%d", machine->screen[y][x]);
        putchar('\n');
    }
}


void fill_screen_with_pattern(CHIP8_Machine* machine) {
    for (size_t y = 0; y < SCREEN_HEIGHT; y++)
        for (size_t x = 0; x < SCREEN_WIDTH; x++)
            machine->screen[y][x] = (y * 5 + x * 3) % 7 < 3;
}

