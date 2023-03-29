//
// Created by Phoebe Mitchell on 29/03/2023.
//

#ifndef CHIP8_C_STACK_H
#define CHIP8_C_STACK_H

typedef struct {
    unsigned short entries[16];
    unsigned char pointer;
} Stack;

#endif //CHIP8_C_STACK_H
