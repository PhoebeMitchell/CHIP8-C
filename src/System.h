//
// Created by Phoebe Mitchell on 31/03/2023.
//

#ifndef CHIP8_C_SYSTEM_H
#define CHIP8_C_SYSTEM_H

#include "Interface/Window.h"
#include "Architecture/Memory.h"
#include "Architecture/Processor.h"
#include "Architecture/Stack.h"
#include <tiff.h>

typedef struct {
    Uint64 lastUpdate;
    Uint64 interval;
} UpdateData;

typedef struct {
    Window window;
    Memory memory;
    Processor processor;
    Stack stack;
    int delayTimer;
    int soundTimer;
    UpdateData updateData;
} System;

System System_Create();
void System_Update(System *system);

#endif //CHIP8_C_SYSTEM_H
