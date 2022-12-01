#pragma once

#include <algorithm>

#include <core.h>
#include <PWMServo.h>

#include <CookieMonsterDrive.h>

namespace CookieMonsterDrive
{
class ServoController
{
public:
    const double max_wheel_angle = 45 * DEG2RAD;

    const int mid_angle;
    const int half_angle;
    PWMServo servo;

    ServoController(const uint8_t servo_pin, const int min_angle, const int max_angle)
        : mid_angle((max_angle + min_angle) / 2), half_angle((max_angle - min_angle) / 2)
    {
        servo.attach(servo_pin);
    }

    ServoController(servo_config_t servo_config)
        : ServoController(servo_config.servo_pin, servo_config.min_angle, servo_config.max_angle)
    {
    }

    void set_wheel_angle(double angle)
    {
        servo.write(std::min(std::max(angle / max_wheel_angle, -1.0), 1.0) * half_angle + mid_angle);
    }
};
} // namespace CookieMonsterDrive
