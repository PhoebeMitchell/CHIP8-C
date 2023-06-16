//
// Created by Phoebe Mitchell on 28/03/2023.
//

#ifndef CHIP8_C_WINDOW_H
#define CHIP8_C_WINDOW_H

#include <SDL.h>
#include "../Architecture/Display.h"
#include "../Architecture/Keypad.h"

typedef struct {
    Uint64 lastUpdate;
    Uint64 interval;
} UpdateData;

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    char isOpen;
    int scale;
    UpdateData updateData;
} Window;

int Window_Initialise();
Window Window_Create(char *title, int width, int height, int scale);
void Window_Close(Window *window);
void Window_PollEvents(Window *window, Keypad keypad);
void Window_Present(Window *window);
void Window_DrawDisplay(Window *window, Display display);
void Window_SetPixel(Window *window, int x, int y, int r, int g, int b, int a);
void Window_Clear(Window *window, SDL_Color clearColor);
void Window_Update(Window *window, Display display);
char Window_ShouldUpdate(Window *window, Keypad keypad);

#endif //CHIP8_C_WINDOW_H
