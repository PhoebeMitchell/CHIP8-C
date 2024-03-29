//
// Created by Phoebe Mitchell on 01/04/2023.
//

#include "Display.h"

void Display_Clear(Display display) {
    const char OFF = 0;
    for (int i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; i++) {
        display[i] = OFF;
    }
}

void Display_Set(Display display, int x, int y, char value) {
    display[Display_LinearCoordinate(x, y)] = value;
}

int Display_LinearCoordinate(int x, int y){
    return y * DISPLAY_WIDTH + x;
}
