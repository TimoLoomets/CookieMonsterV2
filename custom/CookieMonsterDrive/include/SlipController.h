#pragma once
#include <CookieMonsterDrive.h>
#include <AxleController.h>

namespace CookieMonsterDrive
{
class SlipController
{
public:
    AxleController front_controller;
    AxleController rear_controller;

    const double wheel_base = 0.08;
    const double axle_length = 0.07;

    double turn_rate = 0; // 1 / turning_radius(m) -- 0 is straight, positive is left, negative is right
    double speed = 0; // m/s

    SlipController(AxleController front_axle, AxleController rear_axle)
        : front_controller(front_axle), rear_controller(rear_axle)
    {
    }

    void update(const long time_current, const bool logging = false, const bool allow_overclocking = false);
};
}