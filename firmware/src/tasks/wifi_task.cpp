#include "tasks/tasks.h"
#include "wifi_manager.h"

// Wi-Fi Manager Task
void wifi_task(void *pvParameters) {
    WiFiManager::init();

    while (true) {
        // Placeholder for Wi-Fi management logic
        vTaskDelay(1000 / portTICK_PERIOD_MS);  // 1-second delay
    }
}
