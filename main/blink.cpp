#include "core.h"

#include <RGB_LED.h>

int main() {
  pinMode(13, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);

  RGB_LED led(17, 16, 15);

  while (1) {
    // Serial.println("LOOP START");
    // digitalWriteFast(13, HIGH);
    // digitalWriteFast(15, HIGH);
    // digitalWriteFast(16, HIGH);
    // digitalWriteFast(17, HIGH);

    led.set_color(255, 255, 255);
    delay(2000);
    // digitalWriteFast(13, LOW);
    // digitalWriteFast(15, LOW);
    // digitalWriteFast(16, LOW);
    // digitalWriteFast(17, LOW);
    led.set_color(0, 0, 0);

    delay(2000);
  }
}
