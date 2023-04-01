//
// Created by Phoebe Mitchell on 31/03/2023.
//

#include "Processor.h"

Processor Processor_Create(int frequency) {
    Processor processor;
    processor.pc = 0;
    processor.frequency = frequency;
    return processor;
}

Instruction Processor_Fetch(Processor *processor, Memory memory) {
    Instruction instruction;
    instruction.a = memory[processor->pc++];
    instruction.NN = memory[processor->pc++];
    return instruction;
}

DecodedInstruction Processor_Decode(Instruction instruction) {
    DecodedInstruction decodedInstruction;
    decodedInstruction.a = (instruction.a & 0xF0) >> 4;
    decodedInstruction.X = instruction.a & 0xF;
    decodedInstruction.Y = (instruction.NN & 0xF0) >> 4;
    decodedInstruction.N = instruction.NN & 0xF;
    return decodedInstruction;
}
