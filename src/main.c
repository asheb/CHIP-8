#include <stdio.h>
#include <stdlib.h>
#include "machine.h"
#include "loader.h"
#include "debug.h"
#include "ui.h"
#include "util.h"


int main(int argc, char const* argv[]) {
    if (argc != 2) {
        puts("usage: chip8 <filename>");
        return EXIT_FAILURE;
    }

    UI_State ui = { 0 };
    init_UI(&ui);

    CHIP8_Machine machine = { 0 };

    load_rom(&machine, argv[1]);
    //fill_screen_with_pattern(&machine); // for debug

    for (;;) {
        redraw_debug_UI(&machine);
        wait_any_key();
        process_current_instruction(&machine);
    }

    //return EXIT_SUCCESS;
}


