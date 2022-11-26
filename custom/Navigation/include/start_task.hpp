#pragma once

#include <task.hpp>
#include <AckermannController.h>
#include <RGB_LED.h>
#include <memory>
#include <deque>


class StartTask : public Task
{
public:
    long start_time = 0;

    StartTask(Task * task)
        : Task(task)
    {
    }

    bool handle_task(const long current_time) override;
};