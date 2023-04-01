//
// Created by Phoebe Mitchell on 01/04/2023.
//

#include "../src/Architecture/Processor.h"
#include "unity.h"

const int TEST_FREQUENCY = 700;
const unsigned char TEST_MEMORY_VALUE_A = 0xF1;
const unsigned char TEST_MEMORY_VALUE_NN = 0x8E;

Processor processor;

void test_Create() {
    TEST_ASSERT_EQUAL_INT(TEST_FREQUENCY, processor.frequency);
    TEST_ASSERT_EQUAL_INT(0, processor.pc);
}

void test_Fetch() {
    Memory memory;
    memory[0] = TEST_MEMORY_VALUE_A;
    memory[1] = TEST_MEMORY_VALUE_NN;
    Instruction instruction = Processor_Fetch(&processor, memory);
    TEST_ASSERT_EQUAL_CHAR(TEST_MEMORY_VALUE_A, instruction.a);
    TEST_ASSERT_EQUAL_CHAR(TEST_MEMORY_VALUE_NN, instruction.NN);
}

void test_Decode() {
    Instruction instruction;
    instruction.a = TEST_MEMORY_VALUE_A;
    instruction.NN = TEST_MEMORY_VALUE_NN;
    DecodedInstruction decodedInstruction = Processor_Decode(instruction);
    TEST_ASSERT_EQUAL_CHAR(0xF, decodedInstruction.a);
    TEST_ASSERT_EQUAL_CHAR(0x1, decodedInstruction.X);
    TEST_ASSERT_EQUAL_CHAR(0x8, decodedInstruction.Y);
    TEST_ASSERT_EQUAL_CHAR(0xE, decodedInstruction.N);
}

void setUp() {
    processor = Processor_Create(TEST_FREQUENCY);
}

void tearDown() {

}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_Create);
    RUN_TEST(test_Fetch);
    RUN_TEST(test_Decode);
    return UNITY_END();
}
