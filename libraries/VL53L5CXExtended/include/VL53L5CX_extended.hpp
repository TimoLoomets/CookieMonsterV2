#pragma once

#include <SparkFun_VL53L5CX_Library.h>
#include <array>

class VL53L5CXExtended : public SparkFun_VL53L5CX
{
  int shutpin;
  int interrupt_pin;
  uint8_t address;
  void (*interrupt_function)();
  TwoWire i2c;

  VL53L5CX_ResultsData data;

public:
  std::array<int, 4 * 4> distance = {0};
  long last_successful_time = 0;

  VL53L5CXExtended(int shutpin, uint8_t address, TwoWire i2c);
  VL53L5CXExtended(int shutpin, int interrupt_pin, uint8_t address, void (*interrupt_function)());
  bool init();
  void read();
};