#include <CornerController.h>

namespace CookieMonsterDrive
{
void CornerController::update(const long time_current, const bool allow_overclocking)
{
    int32_t encoder_current = encoder.read();
    if (time_last != 0)
    {
        long time_diff = time_current - time_last;
        int32_t encoder_diff = encoder_current - encoder_last;

        if (time_diff != 0)
        {
            
            // Serial.print("Encoder diff: ");
            // Serial.println(encoder_diff);
            // Serial.print("time diff: ");
            // Serial.println((int) time_diff);

            // Serial.print("encoder_ticks_per_rotation: ");
            // Serial.println(encoder_ticks_per_rotation);
            // Serial.print("gearbox_ratio: ");
            // Serial.println(gearbox_ratio);

            // Serial.print("gearbox_ratio: ");
            // Serial.println(gearbox_ratio);
            
            current_speed = encoder_diff / encoder_ticks_per_rotation / gearbox_ratio / (time_diff / 1e3d) * (2 * M_PI * radius);
        }

        if (abs(target_speed) <= 0.01)
        {
            set_speed(0);
        }
        else
        {
            
            // Serial.print("Encoder diff: ");
            // Serial.println(encoder_diff);
            // Serial.print("time diff: ");
            // Serial.println((int) time_diff);

            // Serial.print("encoder_ticks_per_rotation: ");
            // Serial.println(encoder_ticks_per_rotation);
            // Serial.print("gearbox_ratio: ");
            // Serial.println(gearbox_ratio);

            // Serial.print("gearbox_ratio: ");
            // Serial.println(gearbox_ratio);
            
            // current_speed = encoder_diff / encoder_ticks_per_rotation / gearbox_ratio / (time_diff / 1e3d) * (2 * M_PI * radius);
            
            
            double speed_error = current_speed - target_speed;
            Serial.print("[CORNER] speed: ");
            Serial.print(current_speed);
            Serial.print(" ");
            Serial.print(target_speed);
            Serial.print(" ");
            Serial.println(speed_error);
            // Serial.print("speed_step: ");
            // Serial.println(speed_step);
            
            double speed_limit = allow_overclocking ? absolute_speed_limit : safe_speed_limit;
            double step = speed_error * step_direction > 0 ? speed_step * 1.0 : speed_step * 1.5;
            Serial.print("[CORNER] speed_step: ");
            Serial.print(speed_step);
            Serial.print(" ");
            Serial.println(step);
            
            speed = std::min(std::max(-step_direction * sign(speed_error) * step + speed // max(0.2, abs(speed_error)) * 
                                      , -speed_limit), speed_limit);
            Serial.print("[CORNER] set speed: ");
            Serial.println(speed);
            // Serial.println();
            
            set_speed((int16_t) speed);
        }
    }
    else
    {
        // Serial.println("No last time");
    }
    time_last = time_current;
    encoder_last = encoder_current;
}
} // namespace CookieMonsterDrive
