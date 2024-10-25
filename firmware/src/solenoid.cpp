#include "solenoid.h"

// Initialize the solenoid pin
void solenoid_init() {
    pinMode(SOLENOID_PIN, OUTPUT);
    digitalWrite(SOLENOID_PIN, LOW);  // Ensure the lock is closed initially
}

// Function to open the solenoid lock
void open_lock() {
    Serial.println("Lock Opened.");
    digitalWrite(SOLENOID_PIN, HIGH);  // Activate solenoid to open lock
}

// Function to close the solenoid lock
void close_lock() {
    Serial.println("Lock Closed.");
    digitalWrite(SOLENOID_PIN, LOW);   // Deactivate solenoid to close lock
}

