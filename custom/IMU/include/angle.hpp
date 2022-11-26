#pragma once
#include <LSM6.h>

struct Angle
{
  LSM6& imu;

  double x = 0;
  double y = 0;
  double z = 0;
  unsigned long last_time = 0;

  double x_bias = 0;
  double y_bias = 0;
  double z_bias = 0;

  Angle(LSM6& imu)
    : imu(imu)
  {
  }

  void add_single(double& integral, int16_t measurement, double secs, double bias);

  void add_measurement(LSM6::vector<int16_t> measurement);

  void calibrate();

  void zero();
};