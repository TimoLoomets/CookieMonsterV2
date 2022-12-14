#include <task.hpp>
#include <core.h>
#include <string.h>

bool Task::handle_task(const long current_time)
{
    // log("TASK");
    return false;
}

void Task::log(std::string msg)
{
    if(logging)
    {
        Serial.println(msg.c_str());
    }
}

void Task::log(const std::string& msg, const int value)
{
    log(msg + std::to_string(value));
}

void Task::log(const std::string& msg, const double value)
{
    /*if(logging)
    {
        Serial.println(msg.c_str());
        Serial.println(value);
    }*/

    log(msg + std::to_string(value));
}

void Task::log(const std::string& msg, const float value)
{
    log(msg + std::to_string(value));
}

void Task::log(const std::string& msg, const long value)
{
    log(msg + std::to_string(value));
}