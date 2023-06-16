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

void Window_SetKey(int scancode, int value, Keypad keypad) {
    switch (scancode) {
        case SDL_SCANCODE_1:
            keypad[0] = value;
            break;
        case SDL_SCANCODE_2:
            keypad[1] = value;
            break;
        case SDL_SCANCODE_3:
            keypad[2] = value;
            break;
        case SDL_SCANCODE_4:
            keypad[3] = value;
            break;
        case SDL_SCANCODE_Q:
            keypad[4] = value;
            break;
        case SDL_SCANCODE_W:
            keypad[5] = value;
            break;
        case SDL_SCANCODE_E:
            keypad[6] = value;
            break;
        case SDL_SCANCODE_R:
            keypad[7] = value;
            break;
        case SDL_SCANCODE_A:
            keypad[8] = value;
            break;
        case SDL_SCANCODE_S:
            keypad[9] = value;
            break;
        case SDL_SCANCODE_D:
            keypad[10] = value;
            break;
        case SDL_SCANCODE_F:
            keypad[11] = value;
            break;
        case SDL_SCANCODE_Z:
            keypad[12] = value;
            break;
        case SDL_SCANCODE_X:
            keypad[13] = value;
            break;
        case SDL_SCANCODE_C:
            keypad[14] = value;
            break;
        case SDL_SCANCODE_V:
            keypad[15] = value;
            break;
    }
}

void Window_PollEvents(Window *window, Keypad keypad) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
                    Window_Close(window);
                }
                break;
            case SDL_KEYDOWN:
                Window_SetKey(event.key.keysym.scancode, 1, keypad);
                break;
            case SDL_KEYUP:
                Window_SetKey(event.key.keysym.scancode, 0, keypad);
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

void Window_DrawDisplay(Window *window, Display display) {
    for (int i = 0; i < DISPLAY_HEIGHT * DISPLAY_WIDTH; i++) {
        int row = i / DISPLAY_WIDTH;
        int value = 255 * display[i];
        Window_SetPixel(window, i - (row * DISPLAY_WIDTH), row, value, value, value, value);
    }
}

char Window_ShouldUpdate(Window *window, Keypad keypad) {
    Window_PollEvents(window, keypad);
    Uint64 time = SDL_GetTicks64();
    if (window->updateData.lastUpdate + window->updateData.interval <= time) {
        window->updateData.lastUpdate = time;
        return 1;
    }
    return 0;
}

void Window_Update(Window *window, Display display) {
    Window_Clear(window, CLEAR_COLOR);
    Window_DrawDisplay(window, display);
    Window_Present(window);
}
