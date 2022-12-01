#include <start_task.hpp>
#include <straight_task.hpp>


bool StartTask::handle_task(const long current_time)
{
    log("START TASK");
    if (start_time == 0)
    {
        start_time = current_time;
    }

    log("AGE ", current_time - start_time);

    if (current_time - start_time > 1000)
    {
        log("SETTING NEXT TASK");
        // log("START TASK PTR ", (int) next_task.get());
        // next_task = std::make_shared<StraightTask>(controller, indicator, next_task);
        tasks.push_back(std::make_shared<StraightTask>(this));

        return true;
    }

    controller->turn_rate = 0;
    controller->speed = 0.75;
    return false;
}
