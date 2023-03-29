//
// Created by Phoebe Mitchell on 28/03/2023.
//

#include "Window.h"

int Window_Initialise() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("Failed to initialise SDL: %s\n", SDL_GetError());
        return 0;
    }
    return -1;
}

int Window_Create(Window *window, char *title, int width, int height, int scale, int fps) {
    SDL_CreateWindowAndRenderer(width * scale, height * scale, 0, &window->window, &window->renderer);
    if (window->window == NULL || window->renderer == NULL) {
        printf("Failed to create SDL window and renderer: %s\n", SDL_GetError());
        return -1;
    }
    SDL_SetWindowTitle(window->window, title);
    window->updateData.interval = 1000.0f / fps;
    window->updateData.lastUpdate = SDL_GetTicks64();
    window->isOpen = 1;
    window->scale = scale;
    return 0;
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

void Window_Update(Window *window) {
    Window_PollEvents(window);
    uint64 time = SDL_GetTicks64();
    if (window->updateData.lastUpdate + window->updateData.interval > time) {
        return;
    }
    window->updateData.lastUpdate = time;
    Window_Present(window);
}
