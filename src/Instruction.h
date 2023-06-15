//
// Created by Phoebe Mitchell on 15/06/2023.
//

#ifndef CHIP8_C_INSTRUCTION_H
#define CHIP8_C_INSTRUCTION_H

#include "System.h"

#define NN(Y, N) ((Y << 4) | N)
#define NNN(X, Y, N) ((X << 8) | (Y << 4) | N)

void Instruction_SubroutineReturn(System *system);
void Instruction_Jump(System *system, DecodedInstruction decodedInstruction);
void Instruction_Subroutine(System *system, DecodedInstruction decodedInstruction);
void Instruction_SkipEqual_VX_NN(System *system, DecodedInstruction decodedInstruction);
void Instruction_SkipNotEqual_VX_NN(System *system, DecodedInstruction decodedInstruction);
void Instruction_SkipEqual_VX_VY(System *system, DecodedInstruction decodedInstruction);
void Instruction_NotSkipEqual_VX_VY(System *system, DecodedInstruction decodedInstruction);
void Instruction_Set_NN(System *system, DecodedInstruction decodedInstruction);
void Instruction_Add_NN(System *system, DecodedInstruction decodedInstruction);
void Instruction_SetIndex(System *system, DecodedInstruction decodedInstruction);
void Instruction_Set(Processor *processor, DecodedInstruction decodedInstruction);
void Instruction_BinaryOR(Processor *processor, DecodedInstruction decodedInstruction);
void Instruction_BinaryAND(Processor *processor, DecodedInstruction decodedInstruction);
void Instruction_LogicalXOR(Processor *processor, DecodedInstruction decodedInstruction);
void Instruction_Add_VY(Processor *processor, DecodedInstruction decodedInstruction);
void Instruction_Subtract(Processor *processor, DecodedInstruction decodedInstruction);
void Instruction_ShiftLeft(Processor *processor, DecodedInstruction decodedInstruction);
void Instruction_ShiftRight(Processor *processor, DecodedInstruction decodedInstruction);
void Instruction_JumpWithOffset(Processor *processor, DecodedInstruction decodedInstruction);
void Instruction_Random(Processor *processor, DecodedInstruction decodedInstruction);
void Instruction_Display(System *system, DecodedInstruction decodedInstruction);
void Instruction_SkipIfKey(System *system, unsigned char X, unsigned char Y, unsigned char N);
void Instruction_SetVXToDelayTimer(System *system, unsigned char X);
void Instruction_SetDelayTimerToVX(System *system, unsigned char X);
void Instruction_SetSoundTimerToVX(System *system, unsigned char X);
void Instruction_AddToIndex(Processor *processor, unsigned char X);
void Instruction_GetKey(Processor *processor, Keypad keypad, unsigned char X);
void Instruction_FontCharacter(Processor *processor, Memory memory, unsigned char X);
void Instruction_DecimalConversion(Processor *processor, Memory memory, unsigned char X);

#endif //CHIP8_C_INSTRUCTION_H
