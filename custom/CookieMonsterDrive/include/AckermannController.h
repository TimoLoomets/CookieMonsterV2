#pragma once
#include <CookieMonsterDrive.h>
#include <AxleController.h>
#include <ServoController.h>

namespace CookieMonsterDrive
{
class AckermannController
{
public:
    AxleController front_controller;
    AxleController rear_controller;
    ServoController steering_controller;

    const double wheel_base = 0.08;
    const double axle_length = 0.07;

public:
    double turn_rate = 0; // 1 / turning_radius(m) -- 0 is straight, positive is left, negative is right
    double speed = 0; // m/s

    AckermannController(AxleController front_axle, AxleController rear_axle, ServoController servo)
        : front_controller(front_axle)
        , rear_controller(rear_axle)
        , steering_controller(servo)
    {
    }

    void update(const long time_current, const bool logging = false, const bool allow_overclocking = false);
};

} // namespace CookieMonsterDrive
