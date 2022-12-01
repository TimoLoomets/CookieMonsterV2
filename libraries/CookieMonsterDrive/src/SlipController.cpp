#include <SlipController.h>

namespace CookieMonsterDrive
{
    void SlipController::update(const long time_current, const bool logging, const bool allow_overclocking)
    {
        front_controller.M1_controller.target_speed = 0.5;
        front_controller.M2_controller.target_speed = 0.5;
        rear_controller.M1_controller.target_speed = 0.5;
        rear_controller.M2_controller.target_speed = 0.5;

        front_controller.update(time_current, allow_overclocking);
    
        rear_controller.update(time_current, allow_overclocking);
    }
}