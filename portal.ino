#line 2 "portal.ino"

#include "./config.h"
using namespace aunit;

test(correct) {
  int x = 1;
  assertEqual(x, 1);
}

test(incorrect) {
  int x = 1;
  assertNotEqual(x, 1);
}

void setup() {
  Serial.begin(115200);
  Serial.println(F("This test should produce the following:"));
  Serial.println(
    F("1 passed, 1 failed, 0 skipped, 0 timed out, out of 2 test(s).")
  );
  Serial.println(F("----"));
}

void loop() {
  TestRunner::run();
}
