#include <AckermannController.h>

namespace CookieMonsterDrive
{
void AckermannController::update(const unsigned long time_current, const bool logging, const bool allow_overclocking)
{
    if(logging)
    {
        Serial.print("[ACKERMANN] target speed: ");
        Serial.print(speed);
        Serial.print(" turn_rate: ");
        Serial.println(turn_rate);
    }
    double speeds[4] = {speed, speed, speed, speed}; // front_right, front_left, rear_right, rear_left
    if (turn_rate == 0)
    {
        steering_controller.set_wheel_angle(0);
    }
    else
    {
        double turn_radius = 1 / turn_rate; // m
        if(logging)
        {
            Serial.print("[ACKERMANN] turn radius: ");
            Serial.print(turn_radius);
        }
        double turn_angle = std::min(std::max(atan(wheel_base / turn_radius)
                                                   , -steering_controller.max_wheel_angle)
                                     , steering_controller.max_wheel_angle); // rad
        if(logging)
        {
            Serial.print(" turn_angle: ");
            Serial.print(turn_angle);
        }
        steering_controller.set_wheel_angle(-turn_angle);
        turn_radius = wheel_base / tan(turn_angle); // m
        if(logging)
        {
            Serial.print(" real radius: ");
            Serial.println(turn_radius);
        }

        double angular_speed = speed / turn_radius; // rad / s
        speeds[0] = angular_speed * pythagoras(wheel_base, turn_radius + axle_length / 2.0);
        speeds[1] = angular_speed * pythagoras(wheel_base, turn_radius - axle_length / 2.0);
        speeds[2] = angular_speed * (turn_radius + axle_length / 2.0);
        speeds[3] = angular_speed * (turn_radius - axle_length / 2.0);
        if(logging)
        {
            Serial.print("[ACKERMANN] distances: ");
            Serial.print(pythagoras(wheel_base, turn_radius + axle_length / 2.0));
            Serial.print(" ");
            Serial.print(pythagoras(wheel_base, turn_radius - axle_length / 2.0));
            Serial.print(" ");
            Serial.print(turn_radius + axle_length / 2.0);
            Serial.print(" ");
            Serial.println(turn_radius - axle_length / 2.0);

            Serial.print("[ACKERMANN] angular_speed: ");
            Serial.println(angular_speed);
        }
    }

    if(logging)
    {
        Serial.print("[ACKERMANN] speeds: ");
        Serial.print(speeds[0]);
        Serial.print(" ");
        Serial.print(speeds[1]);
        Serial.print(" ");
        Serial.print(speeds[2]);
        Serial.print(" ");
        Serial.println(speeds[3]);
        Serial.println();
    }

    double speed_sign = speed < 0 ? -1 : 1;

    front_controller.set_M1_speed(speed_sign * std::abs(speeds[0]));
    front_controller.set_M2_speed(speed_sign * std::abs(speeds[1]));
    rear_controller.set_M1_speed(speed_sign * std::abs(speeds[2]));
    rear_controller.set_M2_speed(speed_sign * std::abs(speeds[3]));

    front_controller.update(time_current, allow_overclocking);
    rear_controller.update(time_current, allow_overclocking);
}
} // namespace CookieMonsterDrive