#include <cstdint>
#include "teensy4x/pgmspace.h"
// #include <core.h>
void serialEventUSB1() __attribute__((weak));
void serialEventUSB1() {}
uint8_t _serialEventUSB1_default PROGMEM = 1;	
