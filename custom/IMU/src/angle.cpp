#include <angle.hpp>

void Angle::add_single(double& integral, int16_t measurement, double secs, double bias)
{
    // Serial.print("IMU MEASURE");
    // Serial.println(abs(measurement - bias));
    integral += abs(measurement - bias) > 1000 ? (measurement - bias) * secs / 110: 0;
}

void Angle::add_measurement(LSM6::vector<int16_t> measurement)
{
    unsigned long current_time = micros();
    if(last_time != 0)
    {
        double secs = (current_time - last_time) / 1e6;

        add_single(x, measurement.x, secs, x_bias);
        add_single(y, measurement.y, secs, y_bias);
        add_single(z, measurement.z, secs, z_bias);
    }
    last_time = current_time;
}

void Angle::calibrate()
{
    double sums[3] = {0.0, 0.0, 0.0};
    const int loop_count = 100;
    for(int i = 0; i < loop_count; i++)
    {
        imu.read();
        sums[0] += imu.g.x;
        sums[1] += imu.g.y;
        sums[2] += imu.g.z;
        delay(1);
    }
    x_bias = sums[0] / loop_count;
    y_bias = sums[1] / loop_count;
    z_bias = sums[2] / loop_count;
}

void Angle::zero()
{
    x = 0;
    y = 0;
    z = 0;
}