//
// Created by Phoebe Mitchell on 31/03/2023.
//

#ifndef CHIP8_C_SYSTEM_H
#define CHIP8_C_SYSTEM_H

#include "Architecture/Memory.h"
#include "Architecture/Processor.h"
#include "Architecture/Stack.h"
#include "Architecture/Keypad.h"
#include "Architecture/Display.h"

typedef struct {
    Memory memory;
    Processor processor;
    Stack stack;
    Display display;
    int delayTimer;
    int soundTimer;
    Keypad keypad;
} System;

System System_Create();
void System_Update(System *system);

#endif //CHIP8_C_SYSTEM_H
