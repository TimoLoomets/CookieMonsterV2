#pragma once
#include <functional>
#include <algorithm>
#include <math.h>

#include "core.h"
#include <Encoder.h>

#include <CookieMonsterDrive.h>

namespace CookieMonsterDrive
{
class CornerController
{
public:
    Encoder encoder;
    std::function<void(int16_t)> set_speed; // -400...400

    int32_t encoder_last = 0;
    long time_last = 0; // ms
    double radius = 1;           // m
    double gearbox_ratio = 1;
    double encoder_ticks_per_rotation = 1;

    double target_speed = 0; // m/s
    double current_speed = 0;

    double speed = 0; // -400...400
    int step_direction = 1;
    const double speed_step = 4.0;
    const int16_t absolute_speed_limit = 400;
    const int16_t safe_speed_limit = absolute_speed_limit * RECOMMENDED_VOLTAGE / MAX_VOLTAGE;

    CornerController(encoder_pins_t encoder_pins
                     , std::function<void(int16_t)> speed_function
                     , double radius = 0.0175
                     , double gearbox_ratio = 51.45
                     , double encoder_ticks_per_rotation = 12)
        : encoder(encoder_pins.encoder_pin_1, encoder_pins.encoder_pin_2)
        , set_speed(speed_function)
        , radius(radius)
        , gearbox_ratio(gearbox_ratio)
        , encoder_ticks_per_rotation(encoder_ticks_per_rotation)
    {
        Serial.print("ENCODER PINS: ");
        Serial.print(encoder_pins.encoder_pin_1);
        Serial.print(" ");
        Serial.println(encoder_pins.encoder_pin_2);
    }

    CornerController& operator=(CornerController other)
    {
        encoder = other.encoder;
        set_speed = other.set_speed; // -400...400

        encoder_last = other.encoder_last;
        time_last = other.time_last; // ms
        radius = other.radius;           // m
        gearbox_ratio = other.gearbox_ratio;
        encoder_ticks_per_rotation = other.encoder_ticks_per_rotation;

        target_speed = other.target_speed; // m/s
        current_speed = other.current_speed;

        speed = other.speed; // -400...400
        step_direction = other.step_direction;

        return *this;
    }

    void update(const long time_current, const bool allow_overclocking = false);    
};
} // namespace CookieMonsterDrive