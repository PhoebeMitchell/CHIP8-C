//
// Created by Phoebe Mitchell on 01/04/2023.
//

#ifndef CHIP8_C_DISPLAY_H
#define CHIP8_C_DISPLAY_H

#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32
#define PIXEL_OFF 0
#define PIXEL_ON 1

#define Display_LinearCoordinate(x, y) y * DISPLAY_WIDTH + x

typedef char Display[DISPLAY_WIDTH * DISPLAY_HEIGHT];

void Display_Clear(Display display);
void Display_Set(Display display, int x, int y, char value);

#endif //CHIP8_C_DISPLAY_H
