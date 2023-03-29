//
// Created by Phoebe Mitchell on 29/03/2023.
//

#ifndef CHIP8_C_STACK_H
#define CHIP8_C_STACK_H

#define STACK_SIZE 16

typedef struct {
    unsigned short entries[STACK_SIZE];
    unsigned char pointer;
} Stack;

Stack Stack_Create();
void Stack_Push(Stack *stack, unsigned short entry);
unsigned short Stack_Pop(Stack *stack);

#endif //CHIP8_C_STACK_H
