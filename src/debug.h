#pragma once

#include "machine.h"


void print_memory(chip8_machine const* machine, size_t bytes_per_line, size_t starting_address, size_t bytes_to_print);

void print_registers(chip8_machine const* machine);

