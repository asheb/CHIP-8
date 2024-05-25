#include <stdio.h>
#include "loader.h"
#include "machine.h"
#include "util.h"


void load_rom(CHIP8_Machine* machine, char const* file_path) {
    FILE* rom_file = fopen(file_path, "rb");
    if (!rom_file) exit_with_error("can't open the ROM file");

    size_t bytes_read = fread(machine->memory + PROGRAM_BASE_ADDRESS, 1, BYTES_IN_MEMORY - PROGRAM_BASE_ADDRESS, rom_file);
    if (!bytes_read) exit_with_error("the ROM file is empty");
    if (!feof(rom_file)) exit_with_error("can't read the ROM file or it is too big");

    int err = fclose(rom_file);
    if (err) exit_with_error("can't close the ROM file");

    machine->instruction_pointer = PROGRAM_BASE_ADDRESS;
}

