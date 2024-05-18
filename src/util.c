#include <stdio.h>
#include <stdlib.h>


void exit_with_error(char const* error_message) {
    printf("FATAL ERROR: %s\n", error_message);
    exit(EXIT_FAILURE);
}

