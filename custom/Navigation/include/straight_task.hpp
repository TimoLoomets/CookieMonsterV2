#pragma once

#include <task.hpp>
#include <AckermannController.h>
#include <RGB_LED.h>
#include <memory>


class StraightTask : public Task
{
public:
    CookieMonsterDrive::AckermannController* controller;
    RGB_LED& indicator;
    std::shared_ptr<Task> next_task;
    
    long last_enough_distance_time = 0;
    long reverse_until = 0;

    StraightTask(CookieMonsterDrive::AckermannController* controller, RGB_LED& indicator, std::shared_ptr<Task> next_task)
        : controller(controller)
        , indicator(indicator)
        , next_task(next_task)
    {
    }

    void handle_task(const long current_time) override;
};