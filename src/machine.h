#pragma once

#include <stdbool.h>
#include <stdint.h>


#define BYTES_IN_MEMORY 0x1000
#define PROGRAM_BASE_ADDRESS 0x200
#define STACK_SIZE 12
#define DATA_REGISTERS_COUNT 16
#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32


typedef struct chip8_machine chip8_machine;
struct chip8_machine {
    uint8_t memory[BYTES_IN_MEMORY];
    uint8_t data_registers_Vx[DATA_REGISTERS_COUNT];
    uint16_t address_register_I;
    uint16_t return_addresses_stack[STACK_SIZE];
    uint16_t instruction_pointer;
    bool screen[SCREEN_WIDTH][SCREEN_HEIGHT];
};


void process_current_instruction(chip8_machine* machine);

