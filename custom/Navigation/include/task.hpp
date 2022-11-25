#pragma once
#include <string>

class Task
{
public:
    bool logging = false;

    virtual bool handle_task(const long current_time);
    void log(std::string msg);
    void log(const std::string& msg, const int value);
    void log(const std::string& msg, const double value);
    void log(const std::string& msg, const float value);
    void log(const std::string& msg, const long value);
};