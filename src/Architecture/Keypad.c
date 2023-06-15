//
// Created by Phoebe Mitchell on 29/03/2023.
//

#include "Keypad.h"

void Keypad_Initialise(Keypad keypad) {
    for (int i = 0; i < KEYPAD_SIZE; i++) {
        keypad[i] = 0;
    }
}
