#include "core/core.h"

int main() {
  pinMode(13, OUTPUT);

  while (1) {
    // Serial.println("LOOP START");
    digitalWriteFast(13, HIGH);
    delay(200);
    digitalWriteFast(13, LOW);
    delay(200);
  }
}
