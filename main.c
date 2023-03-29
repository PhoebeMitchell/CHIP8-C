#include "src/Font.h"
#include "src/Architecture/Memory.h"
#include "src/Display/Window.h"

const char* WINDOW_NAME = "CHIP8";
const unsigned int WINDOW_WIDTH = 64;
const unsigned int WINDOW_HEIGHT = 32;
const float WINDOW_SCALE = 10;

int main() {
    // Initialise memory
    Memory memory;
    for (int i = 0; i < FONT_SET_SIZE; i++) {
        memory[FONT_SET_ADDRESS + i] = FONT_SET[i];
    }

    // Create window
    Window window;
    Window_Initialise();
    Window_Create(&window, WINDOW_NAME, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_SCALE, 60);
    while (window.isOpen) {
        Window_Update(&window);
    }
    return 0;
}
