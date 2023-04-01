//
// Created by Phoebe Mitchell on 01/04/2023.
//

#include "../src/Architecture/Display.h"
#include "unity.h"

void test_Clear() {
    Display display;
    for (int i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; i++) {
        display[i] = 1;
    }
    char TEST_ARRAY[DISPLAY_WIDTH * DISPLAY_HEIGHT];
    for (int i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; i++) {
        TEST_ARRAY[i] = 1;
    }
    TEST_ASSERT_EQUAL_CHAR_ARRAY(TEST_ARRAY, display, DISPLAY_WIDTH * DISPLAY_HEIGHT);
    for (int i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; i++) {
        TEST_ARRAY[i] = 0;
    }
    Display_Clear(display);
    TEST_ASSERT_EQUAL_CHAR_ARRAY(TEST_ARRAY, display, DISPLAY_WIDTH * DISPLAY_HEIGHT);
}

void test_Set() {
    Display display;
    Display_Clear(display);
    const char X = 4;
    const char Y = 32;
    int LINEAR_COORDINATE = LinearCoordinate(X, Y);
    TEST_ASSERT_EQUAL_CHAR(PIXEL_OFF, display[LINEAR_COORDINATE]);
    Display_Set(display, X, Y, PIXEL_ON);

    TEST_ASSERT_EQUAL_CHAR(PIXEL_ON, display[LINEAR_COORDINATE]);
    Display_Set(display, X, Y, PIXEL_OFF);
    TEST_ASSERT_EQUAL_CHAR(PIXEL_OFF, display[LINEAR_COORDINATE]);
}

void setUp() {

}

void tearDown() {

}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_Clear);
    RUN_TEST(test_Set);
    return UNITY_END();
}
