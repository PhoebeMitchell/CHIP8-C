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
    system.soundTimer = 0;
    system.delayTimer = 0;
    system.updateData.interval = 1000.0f / WINDOW_FPS;
    system.updateData.lastUpdate = SDL_GetTicks64();
    Memory_Initialise(system.memory, FONT_SET, FONT_SET_ADDRESS, FONT_SET_SIZE);
    Window_Initialise();
    Window_Create(&system.window, WINDOW_NAME, DISPLAY_WIDTH, DISPLAY_HEIGHT, WINDOW_SCALE);
    system.processor = Processor_Create(PROCESSOR_FREQUENCY);
    return system;
}

void System_Execute(System *system, DecodedInstruction decodedInstruction) {
    switch (decodedInstruction.a) {
        case 0x0:
            switch (decodedInstruction.Y) {
                case 0xE:
                    switch(decodedInstruction.N) {
                        case 0x0:
                            Window_Clear(&system->window, CLEAR_COLOR);
                            break;
                        case 0xE:
                            system->processor.pc = Stack_Pop(&system->stack);
                    }
            }
            break;
        case 0x1:
            system->processor.pc = NNN(decodedInstruction.X, decodedInstruction.Y, decodedInstruction.N);
            break;
        case 0x2:
            Stack_Push(&system->stack, system->processor.pc);
            system->processor.pc = NNN(decodedInstruction.X, decodedInstruction.Y, decodedInstruction.N);
        case 0x3:
            if (system->processor.V[decodedInstruction.X] == NN(decodedInstruction.Y, decodedInstruction.N)) {
                system->processor.pc++;
            }
            break;
        case 0x4:
            if (system->processor.V[decodedInstruction.X] != (decodedInstruction.Y << 4) | decodedInstruction.N) {
                system->processor.pc++;
            }
            break;
        case 0x5:
            if (system->processor.V[decodedInstruction.X] == system->processor.V[decodedInstruction.Y]) {
                system->processor.pc++;
            }
            break;
        case 0x6:
            system->processor.V[decodedInstruction.X] = NN(decodedInstruction.Y << 4, decodedInstruction.N);
            break;
        case 0x7:
            system->processor.V[decodedInstruction.X] += NN(decodedInstruction.Y, decodedInstruction.N);
            break;
        case 0x9:
            if (system->processor.V[decodedInstruction.X] != system->processor.V[decodedInstruction.Y]) {
                system->processor.pc++;
            }
            break;
        case 0xA:
            system->processor.I = NNN(decodedInstruction.X, decodedInstruction.Y, decodedInstruction.N);
            break;
        case 0xD: {
                unsigned char x = system->processor.V[decodedInstruction.X] % DISPLAY_WIDTH;
                unsigned char y = system->processor.V[decodedInstruction.Y] % DISPLAY_HEIGHT;
                system->processor.V[0xF] = 0;
                for (short i = 0; i < decodedInstruction.N; i++) {
                    unsigned char data = system->memory[system->processor.I + i];
                    const int BYTE_SIZE = 8;
                    for (int i = BYTE_SIZE - 1; i >= 0; i--) {
                        if (data >> i) {

                        }
                    }
                }
            }
            break;
    }
}

void System_Update(System *system) {
    Window_PollEvents(&system->window);
    uint64 time = SDL_GetTicks64();
    if (system->updateData.lastUpdate + system->updateData.interval > time) {
        return;
    }
    system->updateData.lastUpdate = time;

    system->delayTimer -= 1;
    system->soundTimer -= 1;

    Instruction instruction = Processor_Fetch(&system->processor, system->memory);
    DecodedInstruction decodedInstruction = Processor_Decode(instruction);
    System_Execute(system, decodedInstruction);

    Window_Present(&system->window);
}
