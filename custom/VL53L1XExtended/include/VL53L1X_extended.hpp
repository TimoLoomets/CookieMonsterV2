#pragma once
#include <VL53L1X.h>
#include <array>

class VL53L1XExtended : public VL53L1X
{
  int shutpin;
  int interrupt_pin;
  uint8_t address;
  void (*interrupt_function)();

  public:
  static std::array<VL53L1XExtended, 5> sensors;
  int distance;

  VL53L1XExtended(int shutpin, uint8_t address);
  VL53L1XExtended(int shutpin, int interrupt_pin, uint8_t address, void (*interrupt_function)());

  bool init(bool io_2v8 = true);
  void addInterrupt();
  void readInterrupt();
  void clearInterrupt();
  int readWithoutReset();
};