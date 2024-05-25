#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include "ui.h"


void wait_any_key(void) {
    while (get_pressed_key() == PRESSED_KEY_NONE) ;
}


void exit_with_error(char const* error_message) {
    if (ui_initialized) set_color(Color_red);

    printf("\nFATAL ERROR: %s\n", error_message);

    if (ui_initialized) set_color(Color_default);

    printf("press any key to exit\n");
    wait_any_key();

    if (ui_initialized) deinit_UI();

    exit(EXIT_FAILURE);
}

