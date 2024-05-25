#pragma once

#include <stdbool.h>
#include "machine.h"


typedef struct UI_State UI_State;
struct UI_State {
    unsigned terminal_width;
    unsigned terminal_height;
};

extern bool ui_initialized;

typedef enum Color Color;
enum Color {
    Color_default,
    Color_white,
    Color_red,
    Color_dark_gray
};


void init_UI(UI_State* ui);
void deinit_UI(void);

void set_color(Color color);
void set_background_color(Color color);

void draw_screen(CHIP8_Machine const* machine);

void redraw_debug_UI(CHIP8_Machine const* machine);

