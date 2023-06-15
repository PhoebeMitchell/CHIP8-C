//
// Created by Phoebe Mitchell on 28/03/2023.
//

#include "Window.h"

const SDL_Color CLEAR_COLOR = (SDL_Color) {0, 0, 0, 0};

int Window_Initialise() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("Failed to initialise SDL: %s\n", SDL_GetError());
        return 0;
    }
    return -1;
}

Window Window_Create(char *title, int width, int height, int scale) {
    Window window;
    SDL_CreateWindowAndRenderer(width * scale, height * scale, 0, &window.window, &window.renderer);
    if (window.window == NULL || window.renderer == NULL) {
        printf("Failed to create SDL window and renderer: %s\n", SDL_GetError());
        return window;
    }
    SDL_SetWindowTitle(&window, title);
    window.isOpen = 1;
    window.scale = scale;
    return window;
}

void Window_Close(Window *window) {
    window->isOpen = 0;
    SDL_DestroyWindow(window->window);
    SDL_Quit();
}

void Window_PollEvents(Window *window) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
                    Window_Close(window);
                }
                break;
        }
    }
}

void Window_Present(Window *window) {
    SDL_RenderPresent(window->renderer);
}

void Window_SetPixel(Window *window, int x, int y, int r, int g, int b, int a) {
    SDL_Rect rect = {x * window->scale, y * window->scale, window->scale, window->scale};
    SDL_SetRenderDrawColor(window->renderer, r, g, b, a);
    SDL_RenderFillRect(window->renderer, &rect);
}

void Window_Clear(Window *window, SDL_Color clearColor) {
    SDL_SetRenderDrawColor(window->renderer, clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    SDL_RenderClear(window->renderer);
}

void Window_DrawDisplay(Window *window, char *display) {
    for (int i = 0; i < DISPLAY_HEIGHT * DISPLAY_WIDTH; i++) {
        int row = i / DISPLAY_WIDTH;
        int value = 255 * display[i];
        Window_SetPixel(window, i - (row * DISPLAY_WIDTH), row, value, value, value, value);
    }
}

void Window_Update(Window *window, Display *display) {
    Window_PollEvents(window);
    Uint64 time = SDL_GetTicks64();
    if (window->updateData.lastUpdate + window->updateData.interval > time) {
        return;
    }
    Window_Clear(window, CLEAR_COLOR);
    window->updateData.lastUpdate = time;

    Window_DrawDisplay(window, display);
    Window_Present(window);
}
