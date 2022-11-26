#pragma once
#include <string>
#include <imu_wrapper.hpp>
#include <AckermannController.h>
#include <RGB_LED.h>
#include <memory>
#include <deque>

class Task
{
public:
    CookieMonsterDrive::AckermannController* controller;
    RGB_LED& indicator;
    std::deque<std::shared_ptr<Task>>& tasks;
    IMUWrapper& imu;
    bool logging = false;

    Task (CookieMonsterDrive::AckermannController* controller, RGB_LED& indicator, std::deque<std::shared_ptr<Task>>& tasks, IMUWrapper& imu)
        : controller(controller)
        , indicator(indicator)
        , tasks(tasks)
        , imu(imu)
    {
    }

    Task (Task* task)
        : Task(task->controller
            , task->indicator
            , task->tasks
            , task->imu)
    {
    }

    virtual bool handle_task(const long current_time);
    void log(std::string msg);
    void log(const std::string& msg, const int value);
    void log(const std::string& msg, const double value);
    void log(const std::string& msg, const float value);
    void log(const std::string& msg, const long value);
};