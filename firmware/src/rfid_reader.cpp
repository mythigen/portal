#include "rfid_reader.h"

#define RFID_RX 7  // Pin 7 for RX
#define RFID_TX 8  // Pin 8 for TX

SoftwareSerial* RFID = new SoftwareSerial(RFID_RX, RFID_TX);
String text = "";
bool rfidActive = false;

// Initialize the RFID reader
void rfid_init() {
    RFID->begin(9600);
    Serial.println("RFID Reader Initialized. Bring your RFID Card Closer...");
    rfidActive = true;
}

// Read when a card is in range
void rfid_read_card() {
        // Serial.print("Card Read: ");
    if (RFID->available() > 0 && rfidActive) {
        
        // (void)solenoidQueue;
        delay(5);  // Delay to allow for full card read
        char c = RFID->read();
        text += c;
        
        if (text.length() > 20 && rfidActive) {
            Serial.print("Card Read: ");
            Serial.println(text);
            text = "";  // Clear the text buffer
            // int signal = 1;  // Example signal (can be any value, here 1 for simplicity)
            // xQueueSend(solenoidQueue, &signal, portMAX_DELAY);
        }
    }
}

// Stop the RFID reader
void rfid_stop() {
    rfidActive = false;
    Serial.println("RFID Reader Stopped.");
}

// Restart the RFID reader
void rfid_restart() {
    rfidActive = true;
    Serial.println("RFID Reader Restarted. Bring your RFID Card Closer...");
}

