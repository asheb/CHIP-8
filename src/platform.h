#pragma once

#include <stdbool.h>
#include "ui.h"

#define PRESSED_KEY_NONE  '\x0'
#define PRESSED_KEY_ERROR '\xff'


bool do_platform_specific_UI_init(UI_State* ui);

char get_pressed_key(void);

void sleep(unsigned milliseconds);

