#include <VL53L1X_extended.hpp>
#include <core/core.h>
#include <functional>

void interrupt0() {
  VL53L1XExtended::sensors[0].distance = VL53L1XExtended::sensors[0].readWithoutReset();
}

void interrupt1() {
  VL53L1XExtended::sensors[1].distance = VL53L1XExtended::sensors[1].readWithoutReset();
}

void interrupt2() {
  VL53L1XExtended::sensors[2].distance = VL53L1XExtended::sensors[2].readWithoutReset();
}

void interrupt3() {
  VL53L1XExtended::sensors[3].distance = VL53L1XExtended::sensors[3].readWithoutReset();
}

void interrupt4() {
  VL53L1XExtended::sensors[4].distance = VL53L1XExtended::sensors[4].readWithoutReset();
}

std::array<VL53L1XExtended, 5> VL53L1XExtended::sensors = {{
    {37, 38, 0b0000001, interrupt0} // R
    , {9, 10, 0b0000010, interrupt1} // FR
    , {12, 11, 0b0000011, interrupt2} // M
    , {31, 30, 0b0000100, interrupt3} // FL
    , {35, 36, 0b0000101, interrupt4} // L
  }};

VL53L1XExtended::VL53L1XExtended(int shutpin, uint8_t address) : VL53L1XExtended(shutpin, -1, address, nullptr)
{
}

VL53L1XExtended::VL53L1XExtended(int shutpin, int interrupt_pin, uint8_t address, void (*interrupt_function)())
    : shutpin(shutpin)
    , interrupt_pin(interrupt_pin)
    , address(address)
    , interrupt_function(interrupt_function)
{
    pinMode(shutpin, OUTPUT);
    digitalWrite(shutpin, LOW);

    pinMode(interrupt_pin, INPUT);
}

bool VL53L1XExtended::init(bool io_2v8)
{
  digitalWrite(shutpin, HIGH);
  delay(50);
  if(!VL53L1X::init(io_2v8))
  {
    Serial.print("Failed to detect and initialize sensor ");
    Serial.print(address);
    Serial.println();
    return false;
  }
  Serial.print("Successfully detected and initialized sensor ");
  Serial.print(address);
  Serial.println();

  // Use long distance mode and allow up to 50000 us (50 ms) for a measurement.
  // You can change these settings to adjust the performance of the sensor, but
  // the minimum timing budget is 20 ms for short distance mode and 33 ms for
  // medium and long distance modes. See the VL53L1X datasheet for more
  // information on range and timing limits.
  
  // Start continuous readings at a rate of one measurement every 50 ms (the
  // inter-measurement period). This period should be at least as long as the
  // timing budget.
  setAddress(address);
  setTimeout(200);
  Serial.println(io_timeout);
  setDistanceMode(VL53L1X::Long);
  //setMeasurementTimingBudget(33);
  startContinuous(33);

  Serial.print("Successfully configured sensor ");
  Serial.print(address);
  Serial.println();

  delay(100);
  read();
  Serial.println("Successfully completed first read");

  return true;
}

void VL53L1XExtended::addInterrupt()
{
  if (interrupt_pin >= 0)
  {
    std::function<void(void)> interruptFunc = std::bind(&VL53L1XExtended::readInterrupt, this);
    attachInterrupt(digitalPinToInterrupt(interrupt_pin)
        // , &this->readInterrupt
        // , std::bind(&VL53L1XExtended::readInterrupt, this)
        // , interruptFunc//.target<void(*)()>()
        //, std::bind(caller, std::bind(&VL53L1XExtended::readInterrupt, this))
        // , caller
        // , [this](){this->readInterrupt;}
        , interrupt_function
        , RISING);
    Serial.println("Successfully connected interrupt");
  }
}

void VL53L1XExtended::readInterrupt() {
  distance = read();//ranging_data.range_mm;//readWithoutReset();//read();
  Serial.print("DISTANCE ");
  Serial.println(distance);
  uint32_t t = millis();
}

void VL53L1XExtended::clearInterrupt()
{
  writeReg(SYSTEM__INTERRUPT_CLEAR, 0x01); // sys_interrupt_clear_range
}

int VL53L1XExtended::readWithoutReset()
{
  readResults();

  if (!calibrated)
  {
    setupManualCalibration();
    calibrated = true;
  }

  updateDSS();

  getRangingData();

  //writeReg(SYSTEM__INTERRUPT_CLEAR, 0x01); // sys_interrupt_clear_range

  return ranging_data.range_mm;
}