//
// Created by Phoebe Mitchell on 15/06/2023.
//

#include "unity.h"
#include "../src/Instruction.h"

System testSystem;

void Test_SkipIfKey() {
    const int TEST_ADDRESS = 0;
    for (int i = 0; i < KEYPAD_SIZE; i++) {
        testSystem.processor.pc = PROGRAM_ADDRESS;
        testSystem.processor.V[TEST_ADDRESS] = i;
        Instruction_SkipIfKey(&testSystem, TEST_ADDRESS, 0xA, 0x1);
        TEST_ASSERT_EQUAL_INT(PROGRAM_ADDRESS + 1, testSystem.processor.pc);
        testSystem.keypad[testSystem.processor.V[TEST_ADDRESS]] = 1;
        Instruction_SkipIfKey(&testSystem, TEST_ADDRESS, 0x9, 0xE);
        TEST_ASSERT_EQUAL_INT(PROGRAM_ADDRESS + 2, testSystem.processor.pc);
    }
}

void setUp() {
    testSystem = System_Create();
}

void tearDown() {

}

int main() {
    UNITY_BEGIN();
    RUN_TEST(Test_SkipIfKey);
    return UNITY_END();
}
