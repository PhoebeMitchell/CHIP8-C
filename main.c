#include "src/System.h"

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

    int counter = PROGRAM_ADDRESS;
    while (fscanf(file, "%c%c ", &system.memory[counter], &system.memory[counter + 1]) != EOF) {
        counter += 2;
    }
    fclose(file);

    while (system.window.isOpen) {
        System_Update(&system);
    }
    return 0;
}
