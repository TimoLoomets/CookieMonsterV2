#include "core.h"

#include <VL53L5CX_extended.hpp>
#include <TeensyDebug.h>


VL53L5CXExtended sensor1(22, 0x27, Wire1);

int main()
{
    //Serial.begin(115200);
    //Serial.println("START");

    debug.begin(Serial);
    halt_cpu();

    Wire.begin();

    Wire1.begin();
    Wire1.setSCL(16); // change the SCL pin
    Wire1.setSDA(17); // change the SDA pin
    Wire1.setClock(400000); // use 400 kHz I2C

    Serial.println("I2C SETUP DONE");

    pinMode(14, OUTPUT);
    digitalWrite(14, LOW);
    delay(50);
    digitalWrite(14, HIGH);

    Serial.println("POWER ON DONE");

    sensor1.init();

    Serial.println("INIT DONE");

    while(1)
    {
        sensor1.read();

        Serial.print(millis() - sensor1.last_successful_time);
        Serial.print(" DISTANCES: ");
        for(int i=0; i < 16; i++)
        {
            Serial.print(sensor1.distance[i]);
            Serial.print(" ");
        }
        Serial.println();
        delay(10);
    }
}