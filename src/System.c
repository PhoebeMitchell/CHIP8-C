//
// Created by Phoebe Mitchell on 31/03/2023.
//

#include "System.h"
#include "Interface/Window.h"
#include "Architecture/Memory.h"
#include "Architecture/Processor.h"
#include "Font.h"
#include "Architecture/Display.h"
#include "Instruction.h"

const char* WINDOW_NAME = "CHIP8";
const float WINDOW_SCALE = 10;
const float WINDOW_FPS = 60;
const float PROCESSOR_FREQUENCY = 700;

System System_Create() {
    System system;
    srand(time(NULL));
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
                            Instruction_SubroutineReturn(system);
                            break;
                    }
            }
            break;
        case 0x1:
            Instruction_Jump(system, decodedInstruction);
            break;
        case 0x2:
            Instruction_Subroutine(system, decodedInstruction);
            break;
        case 0x3:
            Instruction_SkipEqual_VX_NN(system, decodedInstruction);
            break;
        case 0x4:
            Instruction_SkipNotEqual_VX_NN(system, decodedInstruction);
            break;
        case 0x5:
            Instruction_SkipEqual_VX_VY(system, decodedInstruction);
            break;
        case 0x6:
            Instruction_Set_NN(system, decodedInstruction);
            break;
        case 0x7:
            Instruction_Add_NN(system, decodedInstruction);
            break;
        case 0x8:
            switch (decodedInstruction.N) {
                case 0x0:
                    Instruction_Set(&system->processor, decodedInstruction);
                    break;
                case 0x1:
                    Instruction_BinaryOR(&system->processor, decodedInstruction);
                    break;
                case 0x2:
                    Instruction_BinaryAND(&system->processor, decodedInstruction);
                    break;
                case 0x3:
                    Instruction_LogicalXOR(&system->processor, decodedInstruction);
                    break;
                case 0x4:
                    Instruction_Add_VY(&system->processor, decodedInstruction);
                    break;
                case 0x5:
                    Instruction_Subtract(&system->processor, decodedInstruction);
                    break;
                case 0x6:
                    Instruction_ShiftRight(&system->processor, decodedInstruction);
                    break;
                case 0x7:
                    Instruction_Subtract(&system->processor, decodedInstruction);
                    break;
                case 0xE:
                    Instruction_ShiftLeft(&system->processor, decodedInstruction);
                    break;
            }
            break;
        case 0x9:
            Instruction_NotSkipEqual_VX_VY(system, decodedInstruction);
            break;
        case 0xA:
            Instruction_SetIndex(system, decodedInstruction);
            break;
        case 0xB:
            Instruction_JumpWithOffset(&system->processor, decodedInstruction);
            break;
        case 0xC:
            Instruction_Random(&system->processor, decodedInstruction);
            break;
        case 0xD:
            Instruction_Display(system, decodedInstruction);
            break;
        case 0xE:
            Instruction_SkipIfKey(system, decodedInstruction);
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
