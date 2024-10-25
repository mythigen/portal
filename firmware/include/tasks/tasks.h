#ifndef TASKS_H
#define TASKS_H

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include <LittleFS.h>
#include <ESPAsyncWebServer.h>
#include "../portal.h"


// Task Handles
extern TaskHandle_t wifiTaskHandle;
extern TaskHandle_t httpTaskHandle;
extern TaskHandle_t rfidTaskHandle;
extern TaskHandle_t lockTaskHandle;
extern TaskHandle_t buttonsTaskHandle;
extern TaskHandle_t statusLedTaskHandle;

extern QueueHandle_t solenoidQueue;

// Function Prototypes for Task Initialization
void init_tasks();

// Function Prototypes for Each Task
void wifi_task(void *pvParameters);
void http_task(void *pvParameters);
void rfid_task(void *pvParameters);
void lock_task(void *pvParameters);
void buttons_task(void *pvParameters);
void status_led_task(void *pvParameters);

#endif // TASKS_H
