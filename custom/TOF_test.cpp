#include <array>
#include "core/core.h"

#include <VL53L1XExtended/include/VL53L1X_extended.hpp>

int distance = 0;
uint32_t lastTime = 0;
void myInterrupt();

VL53L1XExtended sensor1(35, 36, 0b0000001, myInterrupt);

void myInterrupt() {
  sensor1.distance = sensor1.read();//ranging_data.range_mm;//readWithoutReset();//read();
  // Serial.print("DISTANCE ");
  Serial.println(sensor1.distance);
  // uint32_t t = millis();
  // Serial.print("DELAY ");
  // Serial.println(t - lastTime);
  // lastTime = t;
}


int main() {
  lastTime = millis();

  pinMode(13, OUTPUT);
  //pinMode(38, INPUT);

  Serial.begin(115200);

  // std::array<VL53L1XExtended, 1> sensors = {{
  //   // {37, 0b0000001} // R
  //   // , {9, 0b0000010} // FR
  //   // , {12, 0b0000011} // M
  //   {31, 0b0000100} // FL
  // }};
    // , {35, 0b0000101}}}; // L
  // VL53L1XExtended sensor1(31, 0b0000001);
  // VL53L1XExtended sensor1(31, 0b0000001);
  // VL53L1XExtended sensor1(31, 0b0000001);
  // VL53L1XExtended sensor1(31, 0b0000001);



  Wire.begin();
  Wire.setClock(400000); // use 400 kHz I2C

  // for(auto sensor : sensors)
  // {
  //   sensor.init();
  // }

  //attachInterrupt(digitalPinToInterrupt(38), myInterrupt, RISING);
  // VL53L1XExtended::sensors[0].addInterrupt();

  for(int i=0; i < VL53L1XExtended::sensors.size(); i++)
  {
    VL53L1XExtended& sensor = VL53L1XExtended::sensors[i];
    sensor.addInterrupt();
    Serial.println("ATTACHED INTERRUPT");
    // int distance = sensor.distance;
    // Serial.print(sensor.distance);
    // Serial.print(" ");
  }

  // VL53L1XExtended::sensors[0].init();
  for(int i=0; i < VL53L1XExtended::sensors.size(); i++)
  {
    VL53L1XExtended& sensor = VL53L1XExtended::sensors[i];
    sensor.init();
    Serial.println(sensor.io_timeout);
  }

  // VL53L1XExtended::sensors[0].read();
  Serial.println("LOOP");
  while (1) {
    static long deelay = millis();
    long diff = millis() - deelay;
    
    Serial.print("Cycle duration: ");
    Serial.println(diff);
    deelay = millis();
    // Serial.println("LOOP START");
    // digitalWriteFast(13, HIGH);
    delay(100);
    // digitalWriteFast(13, LOW);
    // delay(200);
    // digitalWriteFast(13, HIGH);

    Serial.print("READING ");
    for(int i=0; i < VL53L1XExtended::sensors.size(); i++)
    {
      VL53L1XExtended& sensor = VL53L1XExtended::sensors[i];
      // int distance = sensor.distance;
      Serial.print(sensor.distance);
      Serial.print(" ");
    }
    Serial.println();

    Serial.print("AGE ");
    for(int i=0; i < VL53L1XExtended::sensors.size(); i++)
    {
      VL53L1XExtended& sensor = VL53L1XExtended::sensors[i];
      // int distance = sensor.distance;
      Serial.print(deelay - sensor.last_successful_time);
      Serial.print(" ");
    }
    Serial.println();
    
    // Serial.println("MEASURING");
    // for(auto sensor : sensors)
    // {
    //   Serial.print(" READING ");
    //   int distance = sensor.read();
    //   Serial.print(distance);
    //   Serial.print(" ");
    // }
    // Serial.println();
    // int reading = sensor1.read(false);
    // Serial.println(reading);
    //int read = analogRead(30);
    // Serial.println(read);
    //Serial.println(distance);
    //sensor1.clearInterrupt();
    for(int i=0; i < VL53L1XExtended::sensors.size(); i++)
    {
      VL53L1XExtended& sensor = VL53L1XExtended::sensors[i];
      sensor.clearInterrupt();
      // int distance = sensor.distance;
     
    }
  }
}
