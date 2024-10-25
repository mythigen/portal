#include "tasks/tasks.h"
#include "status_led.h"
#include "rfid_reader.h"

void status_led_task(void *pvParameters) {
    while (true) {
        led_show_status(rfidActive);  // Update LED status based on RFID state
        vTaskDelay(1 / portTICK_PERIOD_MS);  // Update LED every 2 seconds
    }
}

