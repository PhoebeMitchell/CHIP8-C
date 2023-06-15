#include "src/System.h"
#include "src/Interface/Window.h"

const char* WINDOW_NAME = "CHIP8";
const float WINDOW_SCALE = 10;
const float WINDOW_FPS = 60;

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("No file specified.");
        return -1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        printf("Failed to open file %s.\n", argv[1]);
        return -1;
    }

    System system = System_Create();

    Window_Initialise();
    Window window = Window_Create((char*)WINDOW_NAME, DISPLAY_WIDTH, DISPLAY_HEIGHT, WINDOW_SCALE);
    window.updateData.interval = 1000.0f / WINDOW_FPS;
    window.updateData.lastUpdate = SDL_GetTicks64();

    int counter = PROGRAM_ADDRESS;
    while (fscanf(file, "%c%c ", &system.memory[counter], &system.memory[counter + 1]) != EOF) {
        counter += 2;
    }
    fclose(file);

    while (window.isOpen) {
        System_Update(&system);
        Window_Update(&window, &system.display);
    }
    Window_Close(&window);
    return 0;
}
