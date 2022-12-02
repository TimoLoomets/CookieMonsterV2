#pragma once

#include <SparkFun_VL53L5CX_Library.h>

class VL53L5CXExtended : public SparkFun_VL53L5CX
{
  int shutpin;
  int interrupt_pin;
  uint8_t address;
  void (*interrupt_function)();
  TwoWire i2c;

public:
  volatile int distance = 0;
  volatile long last_successful_time = 0;

  VL53L5CXExtended(int shutpin, uint8_t address);
  VL53L5CXExtended(int shutpin, int interrupt_pin, uint8_t address, void (*interrupt_function)());
  bool init();
};