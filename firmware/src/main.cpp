#include <Arduino.h>
#include "tasks/tasks.h"

void setup() {
    // Initialize Serial for debugging
    Serial.begin(115200);

    // Initialize tasks
    init_tasks();

    // Optionally: Start other services or initialize peripherals
}

void loop() {
    // Optional: Add any logic to be run continuously in the main loop
}

