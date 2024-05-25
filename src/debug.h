#pragma once

#include "machine.h"


void print_memory(CHIP8_Machine const* machine, size_t bytes_per_line, size_t starting_address, size_t bytes_to_print);

void print_registers(CHIP8_Machine const* machine);

void describe_current_instruction(CHIP8_Machine const* machine);

void print_screen(CHIP8_Machine const* machine);

void fill_screen_with_pattern(CHIP8_Machine* machine);


