//
// Created by Phoebe Mitchell on 31/03/2023.
//

#ifndef CHIP8_C_PROCESSOR_H
#define CHIP8_C_PROCESSOR_H

#include "Memory.h"

static const int REGISTER_SIZE = 16;

typedef struct {
    unsigned char a;
    unsigned char NN;
} Instruction;

typedef struct {
    unsigned char op;
    unsigned char X;
    unsigned char Y;
    unsigned char N;
} DecodedInstruction;

typedef struct {
    int frequency;
    int pc;
    unsigned short I;
    unsigned char V[REGISTER_SIZE];
} Processor;

Processor Processor_Create(int frequency);
Instruction Processor_Fetch(Processor *processor, Memory memory);
DecodedInstruction Processor_Decode(Instruction instruction);

#endif //CHIP8_C_PROCESSOR_H
