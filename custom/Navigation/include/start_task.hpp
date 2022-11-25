#pragma once

#include <task.hpp>
#include <AckermannController.h>
#include <RGB_LED.h>
#include <memory>
#include <deque>


class StartTask : public Task
{
public:
    CookieMonsterDrive::AckermannController* controller;
    RGB_LED& indicator;
    std::deque<std::shared_ptr<Task>>& tasks;
    
    long start_time = 0;

    StartTask(CookieMonsterDrive::AckermannController* controller, RGB_LED& indicator, std::deque<std::shared_ptr<Task>>& tasks)
        : controller(controller)
        , indicator(indicator)
        , tasks(tasks)
    {
    }

    bool handle_task(const long current_time) override;
};