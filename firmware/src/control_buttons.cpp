#include "control_buttons.h"

// Initialize the buttons as input with pull-up resistors
void buttons_init() {
    pinMode(BUTTON_Delta, INPUT_PULLUP);  // For Restart
    pinMode(BUTTON_X, INPUT_PULLUP);      // For Stop
    pinMode(BUTTON_O, INPUT_PULLUP);      // For Start
}

