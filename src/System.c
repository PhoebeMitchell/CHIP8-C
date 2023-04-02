//
// Created by Phoebe Mitchell on 31/03/2023.
//

#include "System.h"
#include "Interface/Window.h"
#include "Architecture/Memory.h"
#include "Architecture/Processor.h"
#include "Font.h"
#include "Architecture/Display.h"

const char* WINDOW_NAME = "CHIP8";
const float WINDOW_SCALE = 10;
const float WINDOW_FPS = 60;
const float PROCESSOR_FREQUENCY = 700;
const SDL_Color CLEAR_COLOR = {0,0,0,0};

#define NN(Y, N) ((Y << 4) | N)
#define NNN(X, Y, N) ((X << 8) | (Y << 4) | N)

System System_Create() {
    System system;
    Display_Clear(system.display);
    system.soundTimer = 0;
    system.delayTimer = 0;
    system.updateData.interval = 1000.0f / WINDOW_FPS;
    system.updateData.lastUpdate = SDL_GetTicks64();
    Memory_Initialise(system.memory, (unsigned char*)FONT_SET, FONT_SET_ADDRESS, FONT_SET_SIZE);
    Window_Initialise();
    Window_Create(&system.window, (char*)WINDOW_NAME, DISPLAY_WIDTH, DISPLAY_HEIGHT, WINDOW_SCALE);
    system.processor = Processor_Create(PROCESSOR_FREQUENCY);
    return system;
}

void System_SubroutineReturn(System *system) {
    system->processor.pc = Stack_Pop(&system->stack);
}

void System_Jump(System *system, DecodedInstruction decodedInstruction) {
    system->processor.pc = NNN(decodedInstruction.X, decodedInstruction.Y, decodedInstruction.N);
}

void System_Subroutine(System *system, DecodedInstruction decodedInstruction) {
    Stack_Push(&system->stack, system->processor.pc);
    system->processor.pc = NNN(decodedInstruction.X, decodedInstruction.Y, decodedInstruction.N);
}

void System_SkipEqual_VX_NN(System *system, DecodedInstruction decodedInstruction) {
    if (system->processor.V[decodedInstruction.X] == NN(decodedInstruction.Y, decodedInstruction.N)) {
        system->processor.pc++;
    }
}

void System_SkipNotEqual_VX_NN(System *system, DecodedInstruction decodedInstruction) {
    if (system->processor.V[decodedInstruction.X] != ((decodedInstruction.Y << 4) | decodedInstruction.N)) {
        system->processor.pc++;
    }
}

void System_SkipEqual_VX_VY(System *system, DecodedInstruction decodedInstruction) {
    if (system->processor.V[decodedInstruction.X] == system->processor.V[decodedInstruction.Y]) {
        system->processor.pc++;
    }
}

void System_NotSkipEqual_VX_VY(System *system, DecodedInstruction decodedInstruction) {
    if (system->processor.V[decodedInstruction.X] != system->processor.V[decodedInstruction.Y]) {
        system->processor.pc++;
    }
}

void System_Set(System *system, DecodedInstruction decodedInstruction) {
    system->processor.V[decodedInstruction.X] = NN(decodedInstruction.Y << 4, decodedInstruction.N);
}

void System_Add(System *system, DecodedInstruction decodedInstruction) {
    system->processor.V[decodedInstruction.X] += NN(decodedInstruction.Y, decodedInstruction.N);
}

void System_SetIndex(System *system, DecodedInstruction decodedInstruction) {
    system->processor.I = NNN(decodedInstruction.X, decodedInstruction.Y, decodedInstruction.N);
}

void System_Display(System *system, DecodedInstruction decodedInstruction) {
    unsigned char x = system->processor.V[decodedInstruction.X] % DISPLAY_WIDTH;
    unsigned char y = system->processor.V[decodedInstruction.Y] % DISPLAY_HEIGHT;
    system->processor.V[0xF] = 0;
    for (short i = 0; i < decodedInstruction.N; i++) {
        unsigned char data = system->memory[system->processor.I + i];
        const int BYTE_SIZE = 8;
        for (int j = BYTE_SIZE - 1; j >= 0; j--) {
            if (data >> j & 0x1) {
                if (system->display[Display_LinearCoordinate(x + (BYTE_SIZE - j), y + i)]) {
                    Display_Set(system->display, x + (BYTE_SIZE - j), y + i, 0);
                    system->processor.V[0xF] = 1;
                } else {
                    Display_Set(system->display, x + (BYTE_SIZE - j), y + i, 1);
                }
            }
        }
    }
}

void System_Execute(System *system, DecodedInstruction decodedInstruction) {
    switch (decodedInstruction.op) {
        case 0x0:
            switch (decodedInstruction.Y) {
                case 0xE:
                    switch(decodedInstruction.N) {
                        case 0x0:
                            Display_Clear(system->display);
                            break;
                        case 0xE:
                            System_SubroutineReturn(system);
                            break;
                    }
            }
            break;
        case 0x1:
            System_Jump(system, decodedInstruction);
            break;
        case 0x2:
            System_Subroutine(system, decodedInstruction);
            break;
        case 0x3:
            System_SkipEqual_VX_NN(system, decodedInstruction);
            break;
        case 0x4:
            System_SkipNotEqual_VX_NN(system, decodedInstruction);
            break;
        case 0x5:
            System_SkipEqual_VX_VY(system, decodedInstruction);
            break;
        case 0x6:
            System_Set(system, decodedInstruction);
            break;
        case 0x7:
            System_Add(system, decodedInstruction);
            break;
        case 0x9:
            System_NotSkipEqual_VX_VY(system, decodedInstruction);
            break;
        case 0xA:
            System_SetIndex(system, decodedInstruction);
            break;
        case 0xD:
            System_Display(system, decodedInstruction);
            break;
    }
}

void System_Update(System *system) {
    Window_PollEvents(&system->window);
    Uint64 time = SDL_GetTicks64();
    if (system->updateData.lastUpdate + system->updateData.interval > time) {
        return;
    }
    Window_Clear(&system->window, (SDL_Color){0, 0, 0, 0});
    system->updateData.lastUpdate = time;

    system->delayTimer -= 1;
    system->soundTimer -= 1;

    Instruction instruction = Processor_Fetch(&system->processor, system->memory);
    DecodedInstruction decodedInstruction = Processor_Decode(instruction);
    System_Execute(system, decodedInstruction);

    Window_DrawDisplay(&system->window, system->display);
    Window_Present(&system->window);
}
