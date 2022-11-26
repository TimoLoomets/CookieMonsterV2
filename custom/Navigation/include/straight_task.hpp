#pragma once

#include <task.hpp>
#include <AckermannController.h>
#include <RGB_LED.h>
#include <memory>
#include <deque>

class StraightTask : public Task
{
public:
    long last_enough_distance_time = 0;
    long last_even_ground_time = 0;
    long last_reverse_time = 0;
    long reverse_until = 0;

    StraightTask(Task * task)
        : Task(task)
    {
    }

    bool handle_task(const long current_time) override;
};