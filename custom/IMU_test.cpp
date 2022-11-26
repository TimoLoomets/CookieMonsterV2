/*
The sensor outputs provided by the library are the raw
16-bit values obtained by concatenating the 8-bit high and
low accelerometer and gyro data registers. They can be
converted to units of g and dps (degrees per second) using
the conversion factors specified in the datasheet for your
particular device and full scale setting (gain).

Example: An LSM6DS33 gives an accelerometer Z axis reading
of 16276 with its default full scale setting of +/- 2 g. The
LA_So specification in the LSM6DS33 datasheet (page 11)
states a conversion factor of 0.061 mg/LSB (least
significant bit) at this FS setting, so the raw reading of
16276 corresponds to 16276 * 0.061 = 992.8 mg = 0.9928 g.
*/

// #include <Wire.h>
#include <core/core.h>
#include <imu_wrapper.hpp>
#include <CookieMonsterDrive.h>
#include <TeensyDebug.h>


// LSM6 imu;

// char report[160];

// Angle angle(imu);
IMUWrapper imu;

void setup()
{
  Serial.begin(115200);
//   debug.begin(Serial);
//   halt_cpu();
//   Wire.begin();

//   if (!imu.init(LSM6::deviceType::device_auto, LSM6::sa0State::sa0_high))
//   {
//     Serial.println("Failed to detect and initialize IMU!");
//     while (1);
//   }
//   imu.enableDefault();
  
//   angle.calibrate();
    imu.init();
}

void loop()
{
//   imu.read();
//   angle.add_measurement(imu.g);
    imu.update(millis());

  /*snprintf(report, sizeof(report), "A: %6d %6d %6d    G: %6d %6d %6d  I:%.2f %.2f %.2f",
    imu.a.x, imu.a.y, imu.a.z,
    imu.g.x, imu.g.y, imu.g.z,
    angle.x, angle.y, angle.z);*/
//  Serial.println(report);
  Serial.print("A: ");
  Serial.print(imu.imu.a.x);
  Serial.print(" ");
  Serial.print(imu.imu.a.y);
  Serial.print(" ");
  Serial.println(imu.imu.a.z);
  Serial.print("G: ");
  Serial.print(imu.imu.g.x);
  Serial.print(" ");
  Serial.print(imu.imu.g.y);
  Serial.print(" ");
  Serial.println(imu.imu.g.z);
  Serial.print("Angle: ");
  Serial.print(imu.angle.x);
  Serial.print(" ");
  Serial.print(imu.angle.y);
  Serial.print(" ");
  Serial.println(imu.angle.z);

  double plane_angle = acos(cos(imu.angle.x * CookieMonsterDrive::DEG2RAD) * cos(imu.angle.y * CookieMonsterDrive::DEG2RAD)) / CookieMonsterDrive::DEG2RAD;
  //atan(sin(imu.angle.x * CookieMonsterDrive::DEG2RAD) / tan(imu.angle.y * CookieMonsterDrive::DEG2RAD));
    //sin(imu.angle.x * CookieMonsterDrive::DEG2RAD) + sin(imu.angle.y * CookieMonsterDrive::DEG2RAD);
  Serial.print("Plane: ");
  Serial.println(plane_angle);

  delay(10);
}

int main()
{
    setup();
    while(1)
    {
        loop();
    }
}