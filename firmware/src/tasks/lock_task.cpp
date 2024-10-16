#include "tasks.h"

// Door Lock Control Task
void lock_task(void *pvParameters) {
    while (true) {
        // Placeholder for door lock control logic
        vTaskDelay(1000 / portTICK_PERIOD_MS);  // 1-second delay
    }
}
