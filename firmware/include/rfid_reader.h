#ifndef RFID_READER_H
#define RFID_READER_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "solenoid.h"
#include "tasks/tasks.h"

extern SoftwareSerial* RFID;
extern bool rfidActive;

// RFID Reader Functions
void rfid_init();
void rfid_read_card();
void rfid_stop();
void rfid_restart();

#endif // RFID_READER_H


// namespace Reader {
//   void check(SoftwareSerial*, String);
// }

