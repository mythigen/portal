#include <Arduino.h>
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "./rfid_reader.h"
// #include "./wifi_manager.h"

#ifndef RFID_RX
#define RFID_RX 7
#endif // !RFID_RX

#ifndef RFID_TX
#define RFID_TX 8
#endif // !RFID_TX

#ifndef LED_1
#define LED_1 47
#endif // !LED_1

#ifndef LED_2
#define LED_2 48
#endif // !LED_1

#ifndef LED_3
#define LED_3 38
#endif // !LED_1

#ifndef BUTTON_Delta
#define BUTTON_Delta 4
#endif // !BUTTON_Delta

#ifndef BUTTON_X
#define BUTTON_X 5
#endif // !BUTTON_X

#ifndef BUTTON_O
#define BUTTON_O 6
#endif // !BUTTON_O

#ifndef SOLENOID
#define SOLENOID 21
#endif // !SOLENOID

#ifndef PORTAL_H
#define PORTAL_H

// namespace Portal {
//   void WiFiMangerTask(void *pvParameters) {
//     (void)pvParameters;
//     WiFiManager::init();
//     for (;;) {
//       vTaskDelay(1000);
//     }
//   }
//   void RFIDTask(void *pvParameters) {}
//   void ButtonTask(void *pvParameters) {}
//   void SolenoidTask(void *pvParameters) {}
//   void LedTask(void *pvParameters) {}
//   void ServerTask(void *pvParameters) {}
//   void init() {
//
//   }
// }

#endif // !PORTAL_H
