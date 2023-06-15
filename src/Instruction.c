//
// Created by Phoebe Mitchell on 15/06/2023.
//

#include <stdlib.h>
#include <printf.h>
#include "Instruction.h"
#include "Font.h"

void Instruction_SubroutineReturn(System *system) {
    system->processor.pc = Stack_Pop(&system->stack);
}

void Instruction_Jump(System *system, DecodedInstruction decodedInstruction) {
    system->processor.pc = NNN(decodedInstruction.X, decodedInstruction.Y, decodedInstruction.N);
}

void Instruction_Subroutine(System *system, DecodedInstruction decodedInstruction) {
    Stack_Push(&system->stack, system->processor.pc);
    system->processor.pc = NNN(decodedInstruction.X, decodedInstruction.Y, decodedInstruction.N);
}

void Instruction_SkipEqual_VX_NN(System *system, DecodedInstruction decodedInstruction) {
    if (system->processor.V[decodedInstruction.X] == NN(decodedInstruction.Y, decodedInstruction.N)) {
        system->processor.pc++;
    }
}

void Instruction_SkipNotEqual_VX_NN(System *system, DecodedInstruction decodedInstruction) {
    if (system->processor.V[decodedInstruction.X] != ((decodedInstruction.Y << 4) | decodedInstruction.N)) {
        system->processor.pc++;
    }
}

void Instruction_SkipEqual_VX_VY(System *system, DecodedInstruction decodedInstruction) {
    if (system->processor.V[decodedInstruction.X] == system->processor.V[decodedInstruction.Y]) {
        system->processor.pc++;
    }
}

void Instruction_NotSkipEqual_VX_VY(System *system, DecodedInstruction decodedInstruction) {
    if (system->processor.V[decodedInstruction.X] != system->processor.V[decodedInstruction.Y]) {
        system->processor.pc++;
    }
}

void Instruction_Set_NN(System *system, DecodedInstruction decodedInstruction) {
    system->processor.V[decodedInstruction.X] = NN(decodedInstruction.Y << 4, decodedInstruction.N);
}

void Instruction_Add_NN(System *system, DecodedInstruction decodedInstruction) {
    system->processor.V[decodedInstruction.X] += NN(decodedInstruction.Y, decodedInstruction.N);
}

void Instruction_SetIndex(System *system, DecodedInstruction decodedInstruction) {
    system->processor.I = NNN(decodedInstruction.X, decodedInstruction.Y, decodedInstruction.N);
}

void Instruction_Set(Processor *processor, DecodedInstruction decodedInstruction) {
    processor->V[decodedInstruction.X] = processor->V[decodedInstruction.Y];
}

void Instruction_BinaryOR(Processor *processor, DecodedInstruction decodedInstruction) {
    processor->V[decodedInstruction.X] |= processor->V[decodedInstruction.Y];
}

void Instruction_BinaryAND(Processor *processor, DecodedInstruction decodedInstruction) {
    processor->V[decodedInstruction.X] &= processor->V[decodedInstruction.Y];
}

void Instruction_LogicalXOR(Processor *processor, DecodedInstruction decodedInstruction) {
    processor->V[decodedInstruction.X] ^= processor->V[decodedInstruction.Y];
}

void Instruction_Add_VY(Processor *processor, DecodedInstruction decodedInstruction) {
    unsigned char oldValue = processor->V[decodedInstruction.X];
    processor->V[decodedInstruction.X] += processor->V[decodedInstruction.Y];
    processor->V[0xF] = processor->V[decodedInstruction.X] < oldValue ? 1 : 0;
}

void Instruction_Subtract(Processor *processor, DecodedInstruction decodedInstruction) {
    processor->V[decodedInstruction.X] = processor->V[decodedInstruction.Y] - processor->V[decodedInstruction.X];
    processor->V[0xF] = decodedInstruction.Y >= decodedInstruction.X ? 1 : 0;
}

void Instruction_ShiftLeft(Processor *processor, DecodedInstruction decodedInstruction) {
    processor->V[decodedInstruction.X] = processor->V[decodedInstruction.Y];
    processor->V[0xF] = processor->V[decodedInstruction.X] & 0x8;
    processor->V[decodedInstruction.X] <<= 1;
}

void Instruction_ShiftRight(Processor *processor, DecodedInstruction decodedInstruction) {
    processor->V[decodedInstruction.X] = processor->V[decodedInstruction.Y];
    processor->V[0xF] = processor->V[decodedInstruction.X] & 0x1;
    processor->V[decodedInstruction.X] >>= 1;
}

void Instruction_JumpWithOffset(Processor *processor, DecodedInstruction decodedInstruction) {
    processor->pc = NNN(decodedInstruction.X, decodedInstruction.Y, decodedInstruction.N) + processor->V[0];
}

void Instruction_Random(Processor *processor, DecodedInstruction decodedInstruction) {
    unsigned char random = rand();
    random &= NN(decodedInstruction.Y, decodedInstruction.N);
    processor->V[decodedInstruction.X] = random;
}

void Instruction_Display(System *system, DecodedInstruction decodedInstruction) {
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

void Instruction_SkipIfKey(System *system, unsigned char X, unsigned char Y, unsigned char N) {
    unsigned char nn = NN(Y, N);
    unsigned char keyPressed = system->keypad[system->processor.V[X]];
    if (nn == 0x9E) {
        if (keyPressed) {
            system->processor.pc++;
        }
    } else if (nn == 0xA1) {
        if (!keyPressed) {
            system->processor.pc++;
        }
    }
}

void Instruction_SetVXToDelayTimer(System *system, unsigned char X) {
    system->processor.V[X] = system->delayTimer;
}

void Instruction_SetDelayTimerToVX(System *system, unsigned char X) {
    system->delayTimer = system->processor.V[X];
}

void Instruction_SetSoundTimerToVX(System *system, unsigned char X) {
    system->soundTimer = system->processor.V[X];
}

void Instruction_AddToIndex(Processor *processor, unsigned char X) {
    processor->I += processor->V[X];
    if (processor->I >= MEMORY_SIZE) {
        processor->V[0xF] = 1;
    }
}

void Instruction_GetKey(Processor *processor, Keypad keypad, unsigned char X) {
    for (int i = 0; i < KEYPAD_SIZE; i++) {
        if (keypad[i]) {
            processor->V[X] = i;
            return;
        }
    }
    processor->pc--;
}

void Instruction_FontCharacter(Processor *processor, Memory memory, unsigned char X) {
    processor->I = memory[FONT_SET_ADDRESS + processor->V[X]];
}

void Instruction_DecimalConversion(Processor *processor, Memory memory, unsigned char X) {
    unsigned char value = processor->V[X];
    const int DIGIT_COUNT = 3;
    for (int i = 0; i < DIGIT_COUNT; i++) {
        memory[processor->I + DIGIT_COUNT - 1 - i] = value % 10;
        value /= 10;
    }
}
