//
// Created by Phoebe Mitchell on 28/03/2023.
//

#include "Memory.h"

void Memory_Initialise(Memory memory, unsigned char *fontSet, int fontSetAddress, int fontSetSize) {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i] = i >= fontSetAddress && i < fontSetAddress + fontSetSize ? fontSet[i - fontSetAddress] : 0;
    }
}
