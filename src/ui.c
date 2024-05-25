#include <stdio.h>
#include "ui.h"
#include "platform.h"
#include "machine.h"
#include "debug.h"
#include "util.h"


#define SPACE 32
#define TOP_HALF 223
#define BOTTOM_HALF 220
#define FULL_BLOCK 219

// UTF-8:
//   lower half block = "\xe2\x96\x84"
//   full block       = "\xe2\x96\x88"
//   upper half block = "\xe2\x96\x80"

bool ui_initialized = false;


static inline void set_cursor_position(unsigned x, unsigned y) {
    printf("\x1b[%u;%uH", y, x);
}

static inline void draw_line(unsigned y, UI_State const* ui) {
    set_cursor_position(1, y);
    printf("\x1b(0");
    for (unsigned i = 0; i < ui->terminal_width; i++)
        putchar('q');
    printf("\x1b(B");
}

void erase_to_the_end_of_the_line() {
    printf("\x1b[K");
}


void init_UI(UI_State* ui) {
    bool ok = do_platform_specific_UI_init(ui);
    if (!ok) exit_with_error("platform-specific UI initialization failed");

    printf("\x1b[?1049h"); // use alternate screen buffer
    printf("\x1b[?25l");   // hide the cursor


    draw_line(1, ui);
    set_cursor_position(ui->terminal_width / 2 - 3, 2);
    puts("CHIP-8");
    draw_line(3, ui);

    draw_line(ui->terminal_height - 2, ui);
    draw_line(ui->terminal_height, ui);

    set_cursor_position(1, 5);

    ui_initialized = true;
}

void deinit_UI(void) {
    printf("\x1b[?1049l"); // switch back to the main buffer
    ui_initialized = false;
}


void set_color(Color color) {
    switch (color) {
        case Color_default:   printf("\x1b[39m"); break;
        case Color_white:     printf("\x1b[97m"); break;
        case Color_red:       printf("\x1b[91m"); break;
        case Color_dark_gray: printf("\x1b[90m"); break;
        default:              exit_with_error("unknown color");
    }
}

void set_background_color(Color color) {
    switch (color) {
        case Color_default:   printf("\x1b[49m"); break;
        case Color_white:     printf("\x1b[107m"); break;
        case Color_red:       printf("\x1b[101m"); break;
        case Color_dark_gray: printf("\x1b[100m"); break;
        default:              exit_with_error("unknown color");
    }
}


void draw_screen(CHIP8_Machine const* machine) {
    static int const block_chars[] = { SPACE, TOP_HALF, BOTTOM_HALF, FULL_BLOCK };

    for (size_t y = 0; y + 1 < SCREEN_HEIGHT; y += 2) {
        for (size_t x = 0; x < SCREEN_WIDTH; x++) {
            bool top    = machine->screen[y][x];
            bool bottom = machine->screen[y + 1][x];
            putchar(block_chars[(top ? 1 : 0) + (bottom ? 2 : 0)]);
        }
        putchar('\n');
    }
}


void redraw_debug_UI(CHIP8_Machine const* machine) {
    set_cursor_position(1, 5);
    draw_screen(machine);
    print_memory(machine, 32, PROGRAM_BASE_ADDRESS, 0x200);
    putchar('\n');
    print_registers(machine);
    putchar('\n');
    describe_current_instruction(machine);
    erase_to_the_end_of_the_line();



}



