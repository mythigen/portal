#include "tasks/tasks.h"
#include "control_buttons.h"   // Include hardware logic
#include "rfid_reader.h"       // Include RFID functions

// Control Buttons Task - Manages RFID actions based on button input
void buttons_task(void *pvParameters) {
    buttons_init();  // Initialize buttons

    while (true) {
        if (digitalRead(BUTTON_O) == LOW) {  // If "O" is pressed
            rfid_init();                     // Start the RFID reader
        }
        if (digitalRead(BUTTON_X) == LOW) {  // If "X" is pressed
            rfid_stop();                     // Stop the RFID reader
        }
        if (digitalRead(BUTTON_Delta) == LOW) {  // If "Delta" is pressed
            rfid_restart();                      // Restart the RFID reader
        }
        vTaskDelay(200 / portTICK_PERIOD_MS);  // Check button state every 200ms
    }
}

