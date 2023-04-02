//
// Created by Phoebe Mitchell on 28/03/2023.
//

#ifndef CHIP8_C_MEMORY_H
#define CHIP8_C_MEMORY_H

#define MEMORY_SIZE 4096
#define PROGRAM_ADDRESS 0x200

typedef unsigned char Memory[MEMORY_SIZE];

void Memory_Initialise(Memory memory, unsigned char *fontSet, int fontSetAddress, int fontSetSize);

#endif //CHIP8_C_MEMORY_H
