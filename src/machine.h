#pragma once

#include <stdbool.h>
#include <stdint.h>


#define BYTES_IN_MEMORY 0x1000
#define PROGRAM_BASE_ADDRESS 0x200
#define STACK_SIZE 12
#define DATA_REGISTERS_COUNT 16
#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32


typedef struct CHIP8_Machine CHIP8_Machine;
struct CHIP8_Machine {
    uint8_t memory[BYTES_IN_MEMORY];
    uint8_t data_registers_Vx[DATA_REGISTERS_COUNT];
    uint16_t address_register_I;
    uint16_t return_addresses_stack[STACK_SIZE];
    uint16_t instruction_pointer;
    bool screen[SCREEN_HEIGHT][SCREEN_WIDTH]; // array of rows, use [y][x] to index
};


typedef struct CHIP8_Instruction CHIP8_Instruction;
struct CHIP8_Instruction {
    uint16_t addr; // address from which the instruction has been read
    uint16_t full; // both bytes of the instruction
    uint8_t  h;    // highest nibble of the instruction
    uint8_t   x;   // second nibble
    uint8_t    y;  // third nibble
    uint8_t     n; // lowest nibble
    uint8_t    nn; // lowest byte
    uint16_t  nnn; // lowest three nibbles
};


CHIP8_Instruction get_current_instruction(CHIP8_Machine const* machine);

void process_current_instruction(CHIP8_Machine* machine);



