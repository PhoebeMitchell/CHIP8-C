//
// Created by Phoebe Mitchell on 31/03/2023.
//

#include "System.h"
#include "Font.h"
#include "Instruction.h"
#include "Interface/Window.h"

const float PROCESSOR_FREQUENCY = 700;

System System_Create() {
    System system;
    srand(time(NULL));
    Display_Clear(system.display);
    system.soundTimer = 0;
    system.delayTimer = 0;
    Memory_Initialise(system.memory, (unsigned char*)FONT_SET, FONT_SET_ADDRESS, FONT_SET_SIZE);
    system.processor = Processor_Create(PROCESSOR_FREQUENCY);
    Keypad_Initialise(system.keypad);
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
            Instruction_SkipIfKey(system, decodedInstruction.X, decodedInstruction.Y, decodedInstruction.N);
            break;
        case 0xF:;
            unsigned char nn = NN(decodedInstruction.Y, decodedInstruction.N);
            switch (nn) {
                case 0x07:
                    Instruction_SetVXToDelayTimer(system, decodedInstruction.X);
                    break;
                case 0x15:
                    Instruction_SetDelayTimerToVX(system, decodedInstruction.X);
                    break;
                case 0x18:
                    Instruction_SetSoundTimerToVX(system, decodedInstruction.X);
                    break;
                case 0x1E:
                    Instruction_AddToIndex(&system->processor, decodedInstruction.X);
                    break;
                case 0x0A:
                    Instruction_GetKey(&system->processor, system->keypad, decodedInstruction.X);
                    break;
                case 0x29:
                    Instruction_FontCharacter(&system->processor, system->memory, decodedInstruction.X);
                    break;
                case 0x33:
                    Instruction_DecimalConversion(&system->processor, system->memory, decodedInstruction.X);
                    break;
            }
            break;
    }
}

void System_Update(System *system) {
    system->delayTimer -= 1;
    system->soundTimer -= 1;

    Instruction instruction = Processor_Fetch(&system->processor, system->memory);
    DecodedInstruction decodedInstruction = Processor_Decode(instruction);
    System_Execute(system, decodedInstruction);
}
