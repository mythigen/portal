#include "tasks.h"
#include "../rfid_reader.h"

void rfid_task(void *pvParameters) {
    rfid_init();  // Initialize the RFID reader

    while (true) {
        // if (rfidActive) {
            rfid_read_card();  // Continuously read card data
        // }
        vTaskDelay(10 / portTICK_PERIOD_MS);  // Check every 100ms
    }
}

