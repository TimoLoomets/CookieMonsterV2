#pragma once
#include <functional>

#include <DualMAX14870Extended.h>

#include <CookieMonsterDrive.h>
#include <CornerController.h>


namespace CookieMonsterDrive
{
class AxleController
{
public:
    DualMAX14870Extended motor_controller;
    CornerController M1_controller;
    CornerController M2_controller;

    AxleController(motor_controller_pins_t motor_controller_pins
                   , encoder_pins_t M1_encoder_pins
                   , encoder_pins_t M2_encoder_pins)
        : motor_controller(motor_controller_pins.M1_dir
                           , motor_controller_pins.M1_pwm
                           , motor_controller_pins.M2_dir
                           , motor_controller_pins.M2_pwm)
        , M1_controller(M1_encoder_pins, std::bind(&DualMAX14870Extended::setM1Speed, &motor_controller, std::placeholders::_1))
        , M2_controller(M2_encoder_pins, std::bind(&DualMAX14870Extended::setM2Speed, &motor_controller, std::placeholders::_1))
    {
    }

    AxleController(axle_pins_t axle_pins)
    : AxleController(axle_pins.motor_controller_pins
                     , axle_pins.M1_encoder_pins
                     , axle_pins.M2_encoder_pins)
    {
    }

    void set_M1_speed(double speed);
    void set_M2_speed(double speed);

    void update(const unsigned long time_current, const bool allow_overclocking = false);
};
}