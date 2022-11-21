#include <core/core.h>
#include <AxleController.h>

CookieMonsterDrive::AxleController rear_axle{{40, 22, 39, 23}, {33, 32}, {34, 41}};
CookieMonsterDrive::AxleController front_axle{{7, 25, 8, 24}, {2, 3}, {4, 5}};

void test_axle(CookieMonsterDrive::AxleController* axle)
{
  axle->motor_controller.setM1Speed(100);
  for(int i = 0; i < 100; i++)
  {
    Serial.print(axle->M1_controller.encoder.read());
    Serial.print(" ; ");
    Serial.println(axle->M2_controller.encoder.read());
    delay(10);
  }
  axle->motor_controller.setM1Speed(-100);
  for(int i = 0; i < 100; i++)
  {
    Serial.print(axle->M1_controller.encoder.read());
    Serial.print(" ; ");
    Serial.println(axle->M2_controller.encoder.read());
    delay(10);
  }
  axle->motor_controller.setM1Speed(0);
  Serial.println();

  axle->motor_controller.setM2Speed(100);
  for(int i = 0; i < 100; i++)
  {
    Serial.print(axle->M1_controller.encoder.read());
    Serial.print(" ; ");
    Serial.println(axle->M2_controller.encoder.read());
    delay(10);
  }
  axle->motor_controller.setM2Speed(-100);
  for(int i = 0; i < 100; i++)
  {
    Serial.print(axle->M1_controller.encoder.read());
    Serial.print(" ; ");
    Serial.println(axle->M2_controller.encoder.read());
    delay(10);
  }
  axle->motor_controller.setM2Speed(0);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("Testing front axle");
  test_axle(&front_axle);
  delay(1000);
  Serial.println("Testing rear axle");
  test_axle(&rear_axle);
  delay(1000);
}

int main()
{
  setup();
  while(1)
  {
    loop();
  }
}