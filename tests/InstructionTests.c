//
// Created by Phoebe Mitchell on 15/06/2023.
//

#include "unity.h"
#include "../src/Instruction.h"
#include "../src/Font.h"

const int TEST_ADDRESS = 0;
System testSystem;

void Test_Clear() {
    const unsigned char testDisplay[DISPLAY_WIDTH * DISPLAY_HEIGHT] = {0};
    for (int i = 0; i < DISPLAY_HEIGHT * DISPLAY_HEIGHT; i++) {
        testSystem.display[i] = 1;
    }
    Instruction_Clear(testSystem.display);
    TEST_ASSERT_EQUAL_CHAR_ARRAY(testDisplay, testSystem.display, DISPLAY_WIDTH * DISPLAY_HEIGHT);
}

void Test_Set_NN() {
    const unsigned char TEST_Y = 5;
    const unsigned char TEST_N = 6;
    const unsigned char EXPECTED_RESULT = 0x56;
    Instruction_Set_NN(&testSystem.processor, TEST_ADDRESS, TEST_Y, TEST_N);
    TEST_ASSERT_EQUAL_CHAR(EXPECTED_RESULT, testSystem.processor.V[TEST_ADDRESS]);
}

void Test_SetIndex() {
    const unsigned char TEST_X = 4;
    const unsigned char TEST_Y = 5;
    const unsigned char TEST_N = 6;
    const unsigned char EXPECTED_RESULT = 0x456;
    Instruction_SetIndex(&testSystem.processor, TEST_X, TEST_Y, TEST_N);
    TEST_ASSERT_EQUAL_CHAR(EXPECTED_RESULT, testSystem.processor.I);
}

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

void Test_StoreMemory() {
    for (int i = 0; i < REGISTER_SIZE; i++) {
        testSystem.processor.V[i] = i;
    }
    Instruction_StoreMemory(&testSystem.processor, testSystem.memory, REGISTER_SIZE);
    for (int i = 0; i < REGISTER_SIZE; i++) {
        TEST_ASSERT_EQUAL_INT(i, testSystem.memory[testSystem.processor.I + i]);
    }
}

void Test_LoadMemory() {
    for (int i = 0; i < REGISTER_SIZE; i++) {
        testSystem.memory[i] = i;
    }
    Instruction_LoadMemory(&testSystem.processor, testSystem.memory, REGISTER_SIZE);
    for (int i = 0; i < REGISTER_SIZE; i++) {
        TEST_ASSERT_EQUAL_INT(i, testSystem.processor.V[i]);
    }
}

void setUp() {
    testSystem = System_Create();
}

void tearDown() {

}

int main() {
    UNITY_BEGIN();
    RUN_TEST(Test_Clear);
    RUN_TEST(Test_Set_NN);
    RUN_TEST(Test_SetIndex);
    RUN_TEST(Test_SkipIfKey);
    RUN_TEST(Test_SetVXToDelayTimer);
    RUN_TEST(Test_SetDelayTimerToVX);
    RUN_TEST(Test_SetSoundTimerToVX);
    RUN_TEST(Test_AddToIndex);
    RUN_TEST(Test_GetKey);
    RUN_TEST(Test_FontCharacter);
    RUN_TEST(Test_DecimalConversion);
    RUN_TEST(Test_StoreMemory);
    RUN_TEST(Test_LoadMemory);
    return UNITY_END();
}
