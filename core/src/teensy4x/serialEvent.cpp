
// #include <core.h>
#include <cstdint>
#include "teensy4x/pgmspace.h"

void serialEvent() __attribute__((weak));
void serialEvent() {
}
uint8_t _serialEvent_default PROGMEM = 1;	
