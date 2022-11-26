#include <hill_task.hpp>
#include <straight_task.hpp>
#include <start_task.hpp>
#include <algorithm>


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

    if(logging)
    {
        Serial.print("x ");
        Serial.println(imu.angle.x);
    }
    if(imu.angle.x < 5
        || current_time - start_time > 3000)
    {
        tasks.push_back(std::make_shared<StartTask>(this));
        tasks.push_back(std::make_shared<StraightTask>(this));
        return true;
    }
    return false;
}
