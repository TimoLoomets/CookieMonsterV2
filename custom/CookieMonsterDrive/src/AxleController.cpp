#include <AxleController.h>
//#include "Arduino.h"

namespace CookieMonsterDrive
{
void AxleController::update(const unsigned long time_current, const bool allow_overclocking)
{
    M1_controller.update(time_current, allow_overclocking);
    M2_controller.update(time_current, allow_overclocking);
}

void AxleController::set_M1_speed(double speed)
{
    M1_controller.target_speed = speed;
}

void AxleController::set_M2_speed(double speed)
{
    M2_controller.target_speed = speed;
}
}