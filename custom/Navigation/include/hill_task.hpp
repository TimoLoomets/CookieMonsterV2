#pragma once

#include <task.hpp>
#include <AckermannController.h>
#include <RGB_LED.h>
#include <memory>


class HillTask : public Task
{
public:
    long last_enough_distance_time = 0;
    long reverse_until = 0;
    long start_time = 0;

    bool reached_middle=false;
    bool reached_lowering=false;

    HillTask(Task * task)
        : Task(task)
    {
    }

    bool handle_task(const long current_time) override;
};