#include <VL53L5CX_extended.hpp>

VL53L5CXExtended::VL53L5CXExtended(int shutpin, uint8_t address, TwoWire i2c)
    : shutpin(shutpin)
    , address(address)
    , i2c(i2c)
{
    pinMode(shutpin, OUTPUT);
    digitalWrite(shutpin, HIGH);
}

bool VL53L5CXExtended::init()
{
    digitalWrite(shutpin, LOW);
    delay(50);
    if(!SparkFun_VL53L5CX::begin(0x29, i2c))
    {
        Serial.print("Failed to detect and initialize sensor ");
        Serial.println(address);
        return false;
    }
    Serial.print("Successfully detected and initialized sensor ");
    Serial.println(address);

    setAddress(address);
    setResolution(4 * 4);
    setRangingFrequency(30);
    setRangingMode(SF_VL53L5CX_RANGING_MODE::CONTINUOUS);
    startRanging();

    return true;
}

void VL53L5CXExtended::read()
{
    if(!isDataReady())
        return;

    getRangingData(&data);
    for (int i = 0; i < 16; i++)
    {
        distance[i] = data.distance_mm[i];
    }
    last_successful_time = millis();
}