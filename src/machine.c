#include <stdio.h>
#include "machine.h"
#include "util.h"
#include "string.h"


void clear_the_screen(chip8_machine* machine) {
    memset(machine->screen, 0, sizeof(machine->screen));
}


void process_current_instruction(chip8_machine* machine) {
    uint16_t ip = machine->instruction_pointer;
    uint16_t instruction = (machine->memory[ip] << 8) + machine->memory[ip + 1];
    uint8_t* vx = machine->data_registers_Vx;

    uint8_t h    =  instruction >> 12;
    uint8_t  x   = (instruction >>  8) & 0xf;
    uint8_t   y  = (instruction >>  4) & 0xf;
    uint8_t    n =  instruction        & 0xf;
    uint8_t   nn =  instruction       & 0xff;
    uint16_t nnn =  instruction      & 0xfff;
    
    printf("instruction = %04x (%x %x %x %x) (NN = %02x) (NNN = %03x)\n", instruction, h, x, y, n, nn, nnn);

    uint16_t next_ip_value = ip + 2;

    if (instruction == 0x00e0) clear_the_screen(machine);
    else if (h ==   6) vx[x] = nn;
    else if (h == 0xa) machine->address_register_I = nnn;
    else exit_with_error("the instruction is not implemented yet");

    machine->instruction_pointer = next_ip_value;
}

