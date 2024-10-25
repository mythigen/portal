#ifndef SOLENOID_H
#define SOLENOID_H

#include <Arduino.h>

#ifndef SOLENOID_PIN
#define SOLENOID_PIN 21  // Pin to control the solenoid (lock)
#endif

// Function Prototypes for Solenoid Control
void solenoid_init();
void open_lock();
void close_lock();

#endif // SOLENOID_H

