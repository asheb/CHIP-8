#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


#define BYTES_IN_MEMORY 0x1000
#define PROGRAM_BASE_ADDRESS 0x200

typedef uint8_t byte;
byte memory[BYTES_IN_MEMORY] = { 0 };


__declspec(noreturn) void exit_with_error(char const* error_message) {
    printf("FATAL ERROR: %s\n", error_message);
    exit(EXIT_FAILURE);
}


void load_rom(char const* file_path) {
    FILE* rom_file = fopen(file_path, "rb");
    if (!rom_file) exit_with_error("can't open the ROM file");

    int bytes_read = fread(memory + PROGRAM_BASE_ADDRESS, 1, BYTES_IN_MEMORY - PROGRAM_BASE_ADDRESS, rom_file);
    if (!bytes_read) exit_with_error("the ROM file is empty");
    if (!feof(rom_file)) exit_with_error("can't read the ROM file or it is too big");

    int err = fclose(rom_file);
    if (err) exit_with_error("can't close the ROM file");
}


void print_memory(size_t bytes_per_line) {
    for (size_t i = 0; i < BYTES_IN_MEMORY; i++) {
        if (i % bytes_per_line == 0) {
            if (i) putchar('\n');
            printf("%04zx: ", i);
        }
        printf("%02x ", memory[i]);
    }
    putchar('\n');
}


int main(int argc, char const* argv[]) {
    if (argc != 2) {
        puts("usage: chip8 <filename>");
        return EXIT_FAILURE;
    }

    load_rom(argv[1]);

    print_memory(32);






    return EXIT_SUCCESS;
}


