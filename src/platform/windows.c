#include <stdio.h>
#include <windows.h>
#include "../platform.h"


bool do_platform_specific_UI_init(UI_State* ui) {
    HANDLE out_h = GetStdHandle(STD_OUTPUT_HANDLE);
    if (out_h == INVALID_HANDLE_VALUE || !out_h) return false;

    DWORD mode = 0;
    BOOL ok = GetConsoleMode(out_h, &mode);
    if (!ok) return false;

    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    //? and perhaps DISABLE_NEWLINE_AUTO_RETURN will be needed as well
    ok = SetConsoleMode(out_h, mode);
    if (!ok) return false;

    CONSOLE_SCREEN_BUFFER_INFO info = { 0 };
    ok = GetConsoleScreenBufferInfo(out_h, &info);
    if (!ok) return false;

    ui->terminal_width = info.srWindow.Right - info.srWindow.Left + 1;
    ui->terminal_height = info.srWindow.Bottom - info.srWindow.Top + 1;

    return true;
}


char get_pressed_key(void) {
    HANDLE in_h = GetStdHandle(STD_INPUT_HANDLE);
    if (in_h == INVALID_HANDLE_VALUE || !in_h) return PRESSED_KEY_ERROR;

    DWORD events = 0;
    BOOL ok = GetNumberOfConsoleInputEvents(in_h, &events);
    if (!ok) return PRESSED_KEY_ERROR;

    if (!events) return PRESSED_KEY_NONE;
    //printf("total events = %lu\n", events);

    INPUT_RECORD input = { 0 };
    DWORD events_read = 0;
    ok = ReadConsoleInput(in_h, &input, 1, &events_read);
    if (!ok || !events_read) return PRESSED_KEY_ERROR;

    if (input.EventType == KEY_EVENT) {
        KEY_EVENT_RECORD* key = &input.Event.KeyEvent;
        if (!key->bKeyDown) return PRESSED_KEY_NONE;
        //printf("keydown = %u, repeats = %hu, keycode = %hu, scancode = %hu, char = '%c', state = %x\n", key->bKeyDown, key->wRepeatCount, key->wVirtualKeyCode, key->wVirtualScanCode, key->uChar.AsciiChar, key->dwControlKeyState);
        return key->uChar.AsciiChar;
    }

    return PRESSED_KEY_NONE;
}


void sleep(unsigned milliseconds) {
    Sleep(milliseconds);
}

