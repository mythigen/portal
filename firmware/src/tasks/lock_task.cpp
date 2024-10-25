#include "tasks/tasks.h"
#include "solenoid.h"

QueueHandle_t solenoidQueue;

// Solenoid Task: Waits for a signal to open the lock, keeps it open for 10 seconds, then closes it
void lock_task(void *pvParameters) {
    
    solenoidQueue = xQueueCreate(10, sizeof(int));
    solenoid_init();  // Initialize the solenoid hardware

    int receivedSignal;
    // digitalWrite(21, HIGH);  // Ensure the lock is closed initially
    // vTaskSuspend(NULL);  // Suspend the task until a signal is received
    while (true) {

        // Wait for a signal from the RFID task (blocking wait)
        if (
            xQueueReceive(solenoidQueue, &receivedSignal, portMAX_DELAY)
            // true
        ) {
            // vTaskSuspend(NULL);  // Suspend the task until a signal is received
            open_lock();  // Open the lock when a card is scanned
            
            // Keep the lock open for 10 seconds
            vTaskDelay(2000 / portTICK_PERIOD_MS);
            
            close_lock();  // Close the lock after 10 seconds

            vTaskDelay(2000 / portTICK_PERIOD_MS);
        }
    }
}

