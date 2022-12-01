#pragma once
#include <cmath>

#include <core.h>

namespace CookieMonsterDrive
{
const double MAX_VOLTAGE = 8.2;
const double RECOMMENDED_VOLTAGE = 6;
const double DEG2RAD = M_PI / 180;

struct encoder_pins_t
{
    uint8_t encoder_pin_1;
    uint8_t encoder_pin_2;
};

struct encoder_configuration_t
{
    encoder_pins_t pins;
    int direction = 1;
};

struct motor_controller_pins_t
{
    uint8_t M1_dir;
    uint8_t M1_pwm;
    uint8_t M2_dir;
    uint8_t M2_pwm;
};

struct axle_pins_t
{
    motor_controller_pins_t motor_controller_pins;
    encoder_pins_t M1_encoder_pins;
    encoder_pins_t M2_encoder_pins;
};

struct servo_config_t
{
    uint8_t servo_pin;
    int min_angle;
    int max_angle;
};


template <typename T> int sign(T val) {
    return (T(0) < val) - (val < T(0));
}

template <typename T> T pythagoras(T a, T b) {
    return std::sqrt(a * a + b * b);
}

} // namespace CookieMonsterDrive
