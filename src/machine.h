#pragma once

#include <stdint.h>


#define BYTES_IN_MEMORY 0x1000
#define PROGRAM_BASE_ADDRESS 0x200
#define STACK_SIZE 12


typedef struct chip8_machine chip8_machine;
struct chip8_machine {
    uint8_t memory[BYTES_IN_MEMORY];
    uint8_t data_registers_Vx[16];
    uint16_t address_register_I;
    uint16_t return_addresses_stack[STACK_SIZE];
    uint16_t instruction_pointer;
};


