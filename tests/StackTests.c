//
// Created by Phoebe Mitchell on 29/03/2023.
//

#include "../src/Architecture/Stack.h"
#include "unity.h"

Stack stack;

void test_Create() {
    TEST_ASSERT_EQUAL_INT(0, stack.pointer);
}

void test_Push() {
    for (int i = 0; i < STACK_SIZE; i++) {
        Stack_Push(&stack, i);
    }
}

void test_Pop() {
    test_Push();
    for (int i = STACK_SIZE - 1; i >= 0; i--) {
        unsigned short entry = Stack_Pop(&stack);
        TEST_ASSERT_EQUAL_INT(i, entry);
    }
}

void setUp() {
    stack = Stack_Create();
}

void tearDown() {
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(&test_Create);
    RUN_TEST(&test_Push);
    RUN_TEST(&test_Pop);
    return UNITY_END();
}
