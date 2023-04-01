//
// Created by Phoebe Mitchell on 31/03/2023.
//

#include "System.h"
#include "Display/Window.h"
#include "Architecture/Memory.h"
#include "Architecture/Processor.h"
#include "Font.h"

const char* WINDOW_NAME = "CHIP8";
const unsigned int WINDOW_WIDTH = 64;
const unsigned int WINDOW_HEIGHT = 32;
const float WINDOW_SCALE = 10;
const float WINDOW_FPS = 60;
const float PROCESSOR_FREQUENCY = 700;
const SDL_Color CLEAR_COLOR = {0,0,0,0};

System System_Create() {
    System system;
    system.soundTimer = 0;
    system.delayTimer = 0;
    system.updateData.interval = 1000.0f / WINDOW_FPS;
    system.updateData.lastUpdate = SDL_GetTicks64();
    Memory_Initialise(system.memory, FONT_SET, FONT_SET_ADDRESS, FONT_SET_SIZE);
    Window_Initialise();
    Window_Create(&system.window, WINDOW_NAME, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_SCALE);
    system.processor = Processor_Create(PROCESSOR_FREQUENCY);
    return system;
}

void System_Execute(System *system, DecodedInstruction decodedInstruction) {
    switch (decodedInstruction.a) {
        case 0x0:
            switch (decodedInstruction.Y) {
                case 0xE:
                    Window_Clear(&system->window, CLEAR_COLOR);
                    break;
            }
            break;
        case 0x1:
            system->processor.pc = decodedInstruction.X | decodedInstruction.Y | decodedInstruction.N;
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
