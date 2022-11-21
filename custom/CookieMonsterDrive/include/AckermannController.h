#pragma once
#include <CookieMonsterDrive.h>
#include <AxleController.h>
#include <ServoController.h>

namespace CookieMonsterDrive
{
class AckermannController
{
private:
    AxleController front_controller;
    AxleController rear_controller;
    ServoController steering_controller;

    const double wheel_base = 0.15;
    const double axle_length = 0.125;

public:
    double turn_rate = 0; // 1 / turning_radius(m) -- 0 is straight, positive is left, negative is right
    double speed = 0; // m/s

    AckermannController(axle_pins_t front_axle_pins, axle_pins_t rear_axle_pins, servo_config_t servo_config)
        : front_controller(front_axle_pins)
        , rear_controller(rear_axle_pins)
        , steering_controller(servo_config)
    {
    }

    void update(const unsigned long time_current, const bool logging = false, const bool allow_overclocking = false);
};

} // namespace CookieMonsterDrive
