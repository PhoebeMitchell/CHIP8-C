//
// Created by Phoebe Mitchell on 29/03/2023.
//

#include "Stack.h"

Stack Stack_Create() {
    Stack stack;
    stack.pointer = 0;
    return stack;
}

void Stack_Push(Stack *stack, unsigned short entry) {
    stack->entries[stack->pointer] = entry;
    stack->pointer++;
}

unsigned short Stack_Pop(Stack *stack) {
    return stack->entries[stack->pointer--];
}
