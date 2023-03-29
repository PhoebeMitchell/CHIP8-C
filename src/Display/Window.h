//
// Created by Phoebe Mitchell on 28/03/2023.
//

#ifndef CHIP8_C_WINDOW_H
#define CHIP8_C_WINDOW_H

#include <SDL.h>
#include <tiff.h>

typedef struct {
    uint64 lastUpdate;
    uint64 interval;
} UpdateData;

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    char isOpen;
    int scale;
    UpdateData updateData;
} Window;

int Window_Initialise();
int Window_Create(Window *window, char *title, int width, int height, int scale, int fps);
void Window_Close(Window *window);
void Window_PollEvents(Window *window);
void Window_Present(Window *window);
void Window_SetPixel(Window *window, int x, int y, int r, int g, int b, int a);
char Window_Update(Window *window);

#endif //CHIP8_C_WINDOW_H
