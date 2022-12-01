#include <imu_wrapper.hpp>

void IMUWrapper::init()
{
    Wire.begin();

    if (!imu.init(LSM6::deviceType::device_auto, LSM6::sa0State::sa0_high))
    {
        Serial.println("Failed to detect and initialize IMU!");
        while (1);
    }
    imu.enableDefault();
    
    angle.calibrate();
}

void IMUWrapper::update(long current_time)
{
    imu.read();
    angle.add_measurement(imu.g);
}

void IMUWrapper::zero()
{
    angle.zero();
}