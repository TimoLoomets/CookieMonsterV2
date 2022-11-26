#pragma once
#include <LSM6.h>
#include <angle.hpp>

class IMUWrapper
{
public:
    LSM6 imu;
    Angle angle;

    IMUWrapper()
        : angle(imu)
    {
    }

    void init();
    void update(long current_time);
    void zero();
};