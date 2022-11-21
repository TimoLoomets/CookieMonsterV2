#include <CornerController.h>

namespace CookieMonsterDrive
{
void CornerController::update(const unsigned long time_current, const bool allow_overclocking)
{
    int32_t encoder_current = encoder.read();
    if (time_last != 0)
    {
        long long time_diff = time_current - time_last;
        int32_t encoder_diff = encoder_current - encoder_last;
        if (time_diff != 0)
        {
            double current_speed = encoder_diff / encoder_ticks_per_rotation / gearbox_ratio / (time_diff / 1e6d) * (2 * M_PI * radius);
            double speed_error = current_speed - target_speed;
            //Serial.print("target: ");
            //Serial.println(target_speed);
            double speed_limit = allow_overclocking ? absolute_speed_limit : safe_speed_limit;
            double step = speed_error > 0 ? speed_step + 15 : speed_step * 1.5;
            speed = std::min(std::max(-1.0 * sign(speed_error) * step + speed // max(0.2, abs(speed_error)) * 
                                      , -speed_limit), speed_limit);
            Serial.print("SETTING SPEED: ");
            Serial.println(speed);
            set_speed((int16_t) speed);
        }
    }
    time_last = time_current;
    encoder_last = encoder_current;
}
} // namespace CookieMonsterDrive
