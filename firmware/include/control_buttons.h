#ifndef CONTROL_BUTTONS_H
#define CONTROL_BUTTONS_H

#include <Arduino.h>

// Button Pin Definitions
#ifndef BUTTON_Delta
#define BUTTON_Delta 4
#endif

#ifndef BUTTON_X
#define BUTTON_X 5
#endif

#ifndef BUTTON_O
#define BUTTON_O 6
#endif

// Function Prototypes for Button Initialization
void buttons_init();

#endif // CONTROL_BUTTONS_H

