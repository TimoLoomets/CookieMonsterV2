#include <hill_task.hpp>


bool HillTask::handle_task(const long current_time)
{
    controller->turn_rate = 0;
    controller->speed = 0.5;
    return false;
}
