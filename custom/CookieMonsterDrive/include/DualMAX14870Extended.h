#pragma once
#include <DualMAX14870MotorShield.h>

namespace CookieMonsterDrive
{
class DualMAX14870Extended : public DualMAX14870MotorShield
{
  public:
  DualMAX14870Extended(uint8_t M1DIR,
                       uint8_t M1PWM,
                       uint8_t M2DIR,
                       uint8_t M2PWM)
                       : DualMAX14870MotorShield(M1DIR, M1PWM, M2DIR, M2PWM, 0xFF, 0xFF)
  {
  }
};
}