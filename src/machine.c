#include <stdio.h>
#include "machine.h"
#include "util.h"
#include "string.h"


static void clear_the_screen(CHIP8_Machine* machine) {
    memset(machine->screen, 0, sizeof(machine->screen));
}


CHIP8_Instruction get_current_instruction(CHIP8_Machine const* machine) {
    uint16_t ip = machine->instruction_pointer;
    uint16_t instruction = (machine->memory[ip] << 8) + machine->memory[ip + 1];

    return (CHIP8_Instruction) {
        .addr =  ip,
        .full =  instruction,
        .h    =  instruction >> 12,
         .x   = (instruction >>  8) & 0xf,
          .y  = (instruction >>  4) & 0xf,
           .n =  instruction        & 0xf,
          .nn =  instruction       & 0xff,
         .nnn =  instruction      & 0xfff
    };
}


void process_current_instruction(CHIP8_Machine* machine) {
    CHIP8_Instruction i = get_current_instruction(machine);
    uint8_t* vx = machine->data_registers_Vx;
    uint16_t next_ip_value = i.addr + 2;

    if (i.full == 0x00e0) clear_the_screen(machine);
    else if (i.h ==   6)  vx[i.x] = i.nn;
    else if (i.h == 0xa)  machine->address_register_I = i.nnn;
    else exit_with_error("the instruction is not implemented yet");

    machine->instruction_pointer = next_ip_value;
}

