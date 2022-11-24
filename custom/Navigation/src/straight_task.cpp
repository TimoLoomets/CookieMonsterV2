#include <straight_task.hpp>
#include <VL53L1X_extended.hpp>
#include <algorithm>

void StraightTask::handle_task(const long current_time)
{
    // log("STRAIGHT DRIVING TASK");

    if(VL53L1XExtended::sensors[2].distance > 250)
    {
        // log("ENOUGH DISTANCE");
        last_enough_distance_time = current_time;
    }

    // log("CHEKS BEGIN");
    if(current_time - last_enough_distance_time > 1000
        && reverse_until == 0)
    {
        // log("TRIGGER REVERSING");
        reverse_until = current_time + 2000;
    } else if (reverse_until < current_time)
    {
        // log("RESETTING REVERSE");
        reverse_until = 0;
    }

    if(current_time < reverse_until)
    {
        // log("REVERSING");
        controller->speed = -0.5;
        controller->turn_rate = 0;
        indicator.set_color(100, 0, 100);
        indicator.period_ms = 100;
        return;
    }
    
    if(VL53L1XExtended::sensors[0].distance > 1000
        && VL53L1XExtended::sensors[1].distance > 1000
        && VL53L1XExtended::sensors[3].distance > 1000
        && VL53L1XExtended::sensors[4].distance > 1000)
    {
        // log("STRAIGHT");
        controller->speed = 0.75;
        controller->turn_rate = 0;
        indicator.set_color(0, 100, 100);
        indicator.period_ms = 1000;
        return;
    }

    double max_turn_rate = 5.0;
    if(VL53L1XExtended::sensors[0].distance < 250
        && VL53L1XExtended::sensors[4].distance < 250)
    {
        // log("CROWDED");
        max_turn_rate = 1.0;
        indicator.period_ms = 200;
    }

    // log("REGULAR AVOIDANCE");
    // log("SETTING COLOR");
    indicator.set_color(0, 100, 100);
    indicator.period_ms = 333;

    // log("SETTING SPEED");
    controller->speed = 0.5;
    // log("CALCULATING MID DIFF");
    long mid_diff = std::clamp(VL53L1XExtended::sensors[1].distance - VL53L1XExtended::sensors[3].distance, -500, 500);
    // log("mid_diff: ", mid_diff);
    //// log("max_turn_rate: ", max_turn_rate);
    // log("CALCULATING TURN RATE");
    double turn_rate = mid_diff / 500.0 * 5.0;
    // log("CLAMPING TURN RATE");
    turn_rate = std::clamp(turn_rate, -max_turn_rate, max_turn_rate);
    // log("SETTING TURN RATE");
    //// log("CONTROLLER PTR: ", (int) controller);
    controller->turn_rate = turn_rate;
    // log("DONE TURN RATE WRITE");
    //// log("turn_rate", controller->turn_rate);
}