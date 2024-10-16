#include "tasks.h"

TaskHandle_t wifiTaskHandle = NULL;
TaskHandle_t httpTaskHandle = NULL;
TaskHandle_t rfidTaskHandle = NULL;
TaskHandle_t lockTaskHandle = NULL;
TaskHandle_t buttonsTaskHandle = NULL;
TaskHandle_t statusLedTaskHandle = NULL;

void init_tasks() {
    // Create the Wi-Fi Manager Task on Core 0
    xTaskCreatePinnedToCore(
        wifi_task,          // Task function
        "WiFiTask",         // Task name
        4096,               // Stack size in bytes
        NULL,               // Task input parameters
        1,                  // Priority
        &wifiTaskHandle,    // Task handle
        0                   // Core 0
    );

    // Create the HTTP Server Task on Core 0
    xTaskCreatePinnedToCore(
        http_task,
        "HttpTask",
        4096,
        NULL,
        1,
        &httpTaskHandle,
        0 // Core 0
    );

    // Create the RFID Reader Task on Core 1
    xTaskCreatePinnedToCore(
        rfid_task,
        "RfidTask",
        2048,
        NULL,
        2, // Higher priority
        &rfidTaskHandle,
        1 // Core 1
    );

    // Create the Door Lock Control Task on Core 1
    xTaskCreatePinnedToCore(
        lock_task,
        "LockTask",
        2048,
        NULL,
        2,
        &lockTaskHandle,
        1
    );

    // Create the Buttons Input Task on Core 1
    xTaskCreatePinnedToCore(
        buttons_task,
        "ButtonsTask",
        2048,
        NULL,
        1,
        &buttonsTaskHandle,
        1
    );

    // Create the Status LED Task on Core 1
    xTaskCreatePinnedToCore(
        status_led_task,
        "StatusLedTask",
        2048,
        NULL,
        1,
        &statusLedTaskHandle,
        1
    );
}
