//
// Created by Phoebe Mitchell on 28/03/2023.
//

#ifndef CHIP8_C_WINDOW_H
#define CHIP8_C_WINDOW_H

#include <SDL.h>

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    char isOpen;
    int scale;
} Window;

int Window_Initialise();
int Window_Create(Window *window, char *title, int width, int height, int scale);
void Window_Close(Window *window);
void Window_PollEvents(Window *window);
void Window_Present(Window *window);
void Window_SetPixel(Window *window, int x, int y, int r, int g, int b, int a);
void Window_Clear(Window *window, SDL_Color clearColor);

#endif //CHIP8_C_WINDOW_H
