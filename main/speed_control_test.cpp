#include <core.h>
#include <AxleController.h>

CookieMonsterDrive::AxleController rear_axle{{40, 22, 39, 23}, {32, 33}, {34, 41, -1}};
CookieMonsterDrive::AxleController front_axle{{7, 25, 8, 24}, {2, 3, -1}, {5, 4}};

void test_axle(CookieMonsterDrive::AxleController* axle)
{
  double test_speed = 0.5;
  axle->set_M1_speed(test_speed);
  for(int i = 0; i < 300; i++)
  {
    axle->update(millis(), false);
    Serial.print("FWD: ");
    Serial.println(axle->M1_controller.current_speed);

    delay(10);
  }
  axle->set_M1_speed(0);
  axle->update(millis(), false);

  Serial.println("Testing reverse");
  axle->set_M1_speed(-test_speed);
  for(int i = 0; i < 300; i++)
  {
    axle->update(millis(), false);
    Serial.print("REV: ");
    Serial.println(axle->M1_controller.current_speed);
    delay(10);
  }
  axle->set_M1_speed(0);
  axle->update(millis(), false);

  Serial.println();

  axle->set_M2_speed(test_speed);
  for(int i = 0; i < 300; i++)
  {
    axle->update(millis(), false);
    Serial.print("FWD: ");
    Serial.println(axle->M2_controller.current_speed);

    delay(10);
  }
  axle->set_M2_speed(0);
  axle->update(millis(), false);

  Serial.println("Testing reverse");
  axle->set_M2_speed(-test_speed);
  for(int i = 0; i < 300; i++)
  {
    axle->update(millis(), false);
    Serial.print("REV: ");
    Serial.println(axle->M2_controller.current_speed);
    delay(10);
  }
  axle->set_M2_speed(0);
  axle->update(millis(), false);

  Serial.println();
}

void setup() {
  Serial.begin(9600);

  //front_axle.M2_controller.step_direction = -1;
  //rear_axle.M1_controller.step_direction = -1;
}

void loop() {
  Serial.println("Testing front axle");
  test_axle(&front_axle);
  delay(5000);
  Serial.println("Testing rear axle");
  test_axle(&rear_axle);
  delay(5000);
}

int main()
{
  setup();
  while(1)
  {
    loop();
  }
}