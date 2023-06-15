//
// Created by Phoebe Mitchell on 15/06/2023.
//

#include "unity.h"
#include "../src/Instruction.h"
#include "../src/Font.h"

const int TEST_ADDRESS = 0;
System testSystem;

void Test_SkipIfKey() {
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

void Test_SetVXToDelayTimer() {
    const int TEST_VALUE = 16;
    testSystem.delayTimer = TEST_VALUE;
    Instruction_SetVXToDelayTimer(&testSystem, TEST_ADDRESS);
    TEST_ASSERT_EQUAL_INT(TEST_VALUE, testSystem.processor.V[TEST_ADDRESS]);
}

void Test_SetDelayTimerToVX() {
    const int TEST_VALUE = 16;
    testSystem.processor.V[TEST_ADDRESS] = TEST_VALUE;
    Instruction_SetDelayTimerToVX(&testSystem, TEST_ADDRESS);
    TEST_ASSERT_EQUAL_INT(TEST_VALUE, testSystem.delayTimer);
}

void Test_SetSoundTimerToVX() {
    const int TEST_VALUE = 16;
    testSystem.processor.V[TEST_ADDRESS] = TEST_VALUE;
    Instruction_SetSoundTimerToVX(&testSystem, TEST_ADDRESS);
    TEST_ASSERT_EQUAL_INT(TEST_VALUE, testSystem.soundTimer);
}

void Test_AddToIndex() {
    const int TEST_VALUE = 1;
    const int INITIAL_INDEX_VALUE = 1;
    const int MAX_INDEX_VALUE = MEMORY_SIZE - 1;
    testSystem.processor.I = INITIAL_INDEX_VALUE;
    testSystem.processor.V[TEST_ADDRESS] = TEST_VALUE;
    testSystem.processor.V[0xF] = 0;
    Instruction_AddToIndex(&testSystem.processor, TEST_ADDRESS);
    TEST_ASSERT_EQUAL_INT(INITIAL_INDEX_VALUE + TEST_VALUE, testSystem.processor.I);
    TEST_ASSERT_EQUAL_INT(0, testSystem.processor.V[0xF]);
    testSystem.processor.I = MAX_INDEX_VALUE;
    Instruction_AddToIndex(&testSystem.processor, TEST_ADDRESS);
    TEST_ASSERT_EQUAL_INT(MAX_INDEX_VALUE + TEST_VALUE, testSystem.processor.I);
    TEST_ASSERT_EQUAL_INT(1, testSystem.processor.V[0xF]);
}

void Test_GetKey() {
    const int KEYPAD_INDEX = 5;
    int originalPCValue = testSystem.processor.pc;
    Instruction_GetKey(&testSystem.processor, testSystem.keypad, TEST_ADDRESS);
    TEST_ASSERT_EQUAL_INT(originalPCValue - 1, testSystem.processor.pc);
    testSystem.keypad[KEYPAD_INDEX] = 1;
    Instruction_GetKey(&testSystem.processor, testSystem.keypad, TEST_ADDRESS);
    TEST_ASSERT_EQUAL_INT(originalPCValue - 1, testSystem.processor.pc);
    TEST_ASSERT_EQUAL_INT(KEYPAD_INDEX, testSystem.processor.V[TEST_ADDRESS]);
}

void Test_FontCharacter() {
    for (int i = 0; i < FONT_SET_SIZE; i++) {
        testSystem.processor.V[TEST_ADDRESS] = i;
        Instruction_FontCharacter(&testSystem.processor, testSystem.memory, TEST_ADDRESS);
        TEST_ASSERT_EQUAL_INT(testSystem.memory[FONT_SET_ADDRESS + i], testSystem.processor.I);
    }
}

void Test_DecimalConversion() {
    const int TEST_VALUE = 123;
    testSystem.processor.V[TEST_ADDRESS] = TEST_VALUE;
    Instruction_DecimalConversion(&testSystem.processor, testSystem.memory, TEST_ADDRESS);
    TEST_ASSERT_EQUAL_CHAR(1, testSystem.memory[testSystem.processor.I]);
    TEST_ASSERT_EQUAL_CHAR(2, testSystem.memory[testSystem.processor.I + 1]);
    TEST_ASSERT_EQUAL_CHAR(3, testSystem.memory[testSystem.processor.I + 2]);
}


void setUp() {
    testSystem = System_Create();
}

void tearDown() {

}

int main() {
    UNITY_BEGIN();
    RUN_TEST(Test_SkipIfKey);
    RUN_TEST(Test_SetVXToDelayTimer);
    RUN_TEST(Test_SetDelayTimerToVX);
    RUN_TEST(Test_SetSoundTimerToVX);
    RUN_TEST(Test_AddToIndex);
    RUN_TEST(Test_GetKey);
    RUN_TEST(Test_FontCharacter);
    RUN_TEST(Test_DecimalConversion);
    return UNITY_END();
}
