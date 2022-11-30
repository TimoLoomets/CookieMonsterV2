#include <hill_task.hpp>
#include <straight_task.hpp>
#include <start_task.hpp>
#include <algorithm>
#include <VL53L1X_extended.hpp>


bool HillTask::handle_task(const long current_time)
{
    if (start_time == 0)
    {
        start_time = current_time;
    }

    indicator.set_color(100, 100, 0);
    indicator.period_ms = 100;
    double turn_rate = std::clamp(-imu.angle.y / 30.0 * 10.0, -10.0, 10.0);
    controller->turn_rate = turn_rate;
    controller->speed = 0.5;

    const double plane_angle = imu.angle.smooth_level;

    if(logging)
    {
        Serial.print("x ");
        Serial.println(imu.angle.x);
    }
    if(plane_angle < 5
        || current_time - start_time > 5000)
    {
        reached_middle=true;
    }


    if(!reached_middle)
    {
        double turn_rate = std::clamp(-imu.angle.y / 30.0 * 10.0, -10.0, 10.0);
        controller->turn_rate = turn_rate;
        controller->speed = 0.5;
    }
    else
    {
        if (plane_angle > 10
            && current_time - start_time < 10000)
        {
            reached_lowering = true;
        }

        if (!reached_lowering)
        {
            double min_distance = std::min({VL53L1XExtended::sensors[0].distance
                , VL53L1XExtended::sensors[1].distance
                , VL53L1XExtended::sensors[2].distance
                , VL53L1XExtended::sensors[3].distance
                , VL53L1XExtended::sensors[4].distance});

            controller->speed = std::clamp(min_distance / 100 * 0.25 , 0.3, 1.0);
            long mid_diff = std::clamp(VL53L1XExtended::sensors[3].distance - VL53L1XExtended::sensors[1].distance, -500, 500);
            double turn_rate = mid_diff / 500.0 * 7.0;
            turn_rate = std::clamp(turn_rate, -7.0, 7.0);
            controller->turn_rate = turn_rate;
        }
        else if (plane_angle > 10)
        {
            double turn_rate = std::clamp(imu.angle.y / 30.0 * 10.0, -10.0, 10.0);
            controller->turn_rate = turn_rate;
            controller->speed = 0.5;
        }
        else
        {
            tasks.push_back(std::make_shared<StartTask>(this));
            tasks.push_back(std::make_shared<StraightTask>(this));
            return true;
        }
    }
            
    return false;
}
