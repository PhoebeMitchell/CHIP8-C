//
// Created by Phoebe Mitchell on 29/03/2023.
//

#ifndef CHIP8_C_KEYPAD_H
#define CHIP8_C_KEYPAD_H

static const unsigned int KEYPAD_SIZE = 16;

typedef unsigned char Keypad[KEYPAD_SIZE];

void Keypad_Initialise(Keypad keypad);

#endif //CHIP8_C_KEYPAD_H
