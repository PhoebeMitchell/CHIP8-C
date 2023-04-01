//
// Created by Phoebe Mitchell on 31/03/2023.
//

#ifndef CHIP8_C_PROCESSOR_H
#define CHIP8_C_PROCESSOR_H

#include "Memory.h"

typedef struct {
    unsigned char a;
    unsigned char NN;
} Instruction;

typedef struct {
    unsigned char a;
    unsigned char X;
    unsigned char Y;
    unsigned char N;
} DecodedInstruction;

typedef struct {
    int frequency;
    int pc;
    short I;
    unsigned char V[16];
} Processor;

Processor Processor_Create(int frequency);
Instruction Processor_Fetch(Processor *processor, Memory memory);
DecodedInstruction Processor_Decode(Instruction instruction);

#endif //CHIP8_C_PROCESSOR_H
