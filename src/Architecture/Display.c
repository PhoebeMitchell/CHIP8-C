//
// Created by Phoebe Mitchell on 01/04/2023.
//

#include <printf.h>
#include "Display.h"

void Display_Clear(Display display) {
    const char OFF = 0;
    for (int i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; i++) {
        display[i] = OFF;
    }
}

void Display_Set(Display display, int x, int y, char value) {
    display[LinearCoordinate(x, y)] = value;
}
