//
// Created by Phoebe Mitchell on 29/03/2023.
//

#include "../src/Architecture/Memory.h"
#include "unity.h"
#include "../src/Font.h"

void test_Initialise() {
    Memory memory;
    Memory_Initialise(memory, FONT_SET, FONT_SET_ADDRESS, FONT_SET_SIZE);

    for (int i = 0; i < MEMORY_SIZE; i++) {
        TEST_ASSERT_EQUAL_INT(memory[i], i >= FONT_SET_ADDRESS && i < FONT_SET_ADDRESS + FONT_SET_SIZE ? FONT_SET[i - FONT_SET_ADDRESS] : 0);
    }
}

void setUp() {

}

void tearDown() {

}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_Initialise);
    return UNITY_END();
}
