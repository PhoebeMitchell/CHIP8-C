//
// Created by Phoebe Mitchell on 15/06/2023.
//

#ifndef CHIP8_C_INSTRUCTION_H
#define CHIP8_C_INSTRUCTION_H

#include "System.h"

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
void Instruction_SkipIfKey(System *system, DecodedInstruction decodedInstruction);

#endif //CHIP8_C_INSTRUCTION_H
