#include "status_led.h"

#define LED_1 47
#define LED_2 48
#define LED_3 38

// Function to indicate status on the LEDs
void led_show_status(bool active) {
    if (active) {
        digitalWrite(LED_1, HIGH);  // Turn on LED for active status
    } else {
        digitalWrite(LED_1, LOW);   // Turn off LED for inactive status
    }
}

