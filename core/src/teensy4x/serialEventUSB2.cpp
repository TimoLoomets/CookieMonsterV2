#include <cstdint>
#include "teensy4x/pgmspace.h"
// #include <core.h>
void serialEventUSB2() __attribute__((weak));
void serialEventUSB2() {}
uint8_t _serialEventUSB2_default PROGMEM = 1;	
