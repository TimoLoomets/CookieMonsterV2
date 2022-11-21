#pragma once
#include <functional>
#include <algorithm>
#include <math.h>

#include "core/core.h"
#include <Encoder.h>

#include <CookieMonsterDrive.h>

namespace CookieMonsterDrive
{
class CornerController
{
public:
    Encoder encoder;
    std::function<void(int16_t)> set_speed; // -400...400

    int32_t encoder_last;
    unsigned long time_last; // us
    double radius;           // m
    double gearbox_ratio = 1;
    double encoder_ticks_per_rotation = 1;

    double target_speed; // m/s

    double speed; // -400...400
    const double speed_step = 4;
    const int16_t absolute_speed_limit = 400;
    const int16_t safe_speed_limit = absolute_speed_limit * RECOMMENDED_VOLTAGE / MAX_VOLTAGE;

    CornerController(encoder_pins_t encoder_pins
                     , std::function<void(int16_t)> speed_function
                     , double radius = 0.025
                     , double gearbox_ratio = 51.45
                     , double encoder_ticks_per_rotation = 12)
        : encoder(encoder_pins.encoder_pin_1, encoder_pins.encoder_pin_2)
        , set_speed(speed_function)
        , radius(radius)
        , gearbox_ratio(gearbox_ratio)
        , encoder_ticks_per_rotation(encoder_ticks_per_rotation)
    {
    }

    void update(const unsigned long time_current, const bool allow_overclocking = false);    
};
} // namespace CookieMonsterDrive