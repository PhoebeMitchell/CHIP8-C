#include "src/System.h"

int main() {
    System system = System_Create();
    while (system.window.isOpen) {
        System_Update(&system);
    }
    return 0;
}
