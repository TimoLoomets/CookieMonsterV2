#include <core/core.h>
#include <AckermannController.h>
#include <VL53L1X_extended.hpp>
#include <RGB_LED.h>
#include <navigation.hpp>
#include <imu_wrapper.hpp>

#include <memory>
#include <deque>

#include <TeensyDebug.h>

int main()
{
    delay(1000);
    RGB_LED indicator(16, 15, 17);
    indicator.set_color(0, 0, 100);

    const int switch_pin = 6;
    pinMode(6, switch_pin);

    IMUWrapper imu;
    imu.init();

    CookieMonsterDrive::AckermannController controller{{{7, 25, 8, 24}, {2, 3, -1}, {5, 4, 1}}
                                                 , {{39, 23, 40, 22}, {34, 41, -1}, {32, 33, 1}}
                                                 , {0, 65, 145}};

    /*
    CookieMonsterDrive::AxleController rear_axle{{39, 23, 40, 22}, {34, 41, -1}, {32, 33}};
    CookieMonsterDrive::AxleController front_axle{{7, 25, 8, 24}, {3, 2, -1}, {4, 5}};
    controller.front_controller = front_axle;
    controller.rear_controller = rear_axle;
    */

    Wire.begin();
    Wire.setClock(400000);

    for(auto& sensor : VL53L1XExtended::sensors)
    {
        sensor.addInterrupt();
    }
    for(auto& sensor : VL53L1XExtended::sensors)
    {
        while(!sensor.init());
    }

    indicator.set_color(0, 100, 0);
    indicator.period_ms = 0;

    Serial.begin(115200);
    // debug.begin(Serial);
    // halt_cpu();

    while(digitalRead(switch_pin));
    indicator.set_color(100, 0, 0);
    while(!digitalRead(switch_pin));
    indicator.period_ms = 500;
    for(int i=0; i < 500; i++)
    {
        indicator.refresh(millis());
        delay(10);
    }

    indicator.set_color(0, 0, 100);
    indicator.period_ms = 0;

    const bool logging = false;
    const bool move = true;

    //std::shared_ptr<Task> next_task;
    std::deque<std::shared_ptr<Task>> tasks;
    Task base_task(&controller, indicator, tasks, imu);
    tasks.push_back(std::make_shared<StartTask>(&base_task));
    imu.zero();

    //current_task = std::make_shared<StartTask>(&controller, indicator, next_task);
    //current_task->logging = logging;

    while(1)
    {
        if(logging)
        {
            Serial.print("READING ");
            for(auto& sensor : VL53L1XExtended::sensors)
            {
                Serial.print(sensor.distance);
                Serial.print(" ");
            }
            Serial.println();
        }
                
        long current_time = millis();
        imu.update(current_time);

        if(tasks.size() > 0)
        {
            // Serial.print("POINTER EXISTANCES: ");
            // Serial.println(current_task.use_count());
            bool finished = tasks[0]->handle_task(current_time);
            if(finished)
            {
                tasks.pop_front();
            }
        }
        else if(logging)
        {
            Serial.println("NO TASK");
        }
        
        /*
        controller.speed = 0.2;

        double side_diff = VL53L1XExtended::sensors[0].distance - VL53L1XExtended::sensors[4].distance; 
        double mid_diff = VL53L1XExtended::sensors[1].distance - VL53L1XExtended::sensors[3].distance; 

        if (side_diff > 500) {
            controller.turn_rate = 3;
        } else if (side_diff < -500) {
            controller.turn_rate = -3;
        } else {
            controller.turn_rate = 0.0;
        }*/

        if(move)
        {
            controller.update(current_time);
        }

        if(logging)
        {
            /*
            Serial.print("Encoder: ");
            Serial.print(controller.front_controller.M1_controller.encoder.read());
            Serial.print(" ");
            Serial.print(controller.front_controller.M2_controller.encoder.read());
            Serial.print(" ");
            Serial.print(controller.rear_controller.M1_controller.encoder.read());
            Serial.print(" ");
            Serial.println(controller.rear_controller.M2_controller.encoder.read());
            */
            Serial.print("Speeds: ");
            Serial.print(controller.front_controller.M1_controller.current_speed);
            Serial.print(" ");
            Serial.print(controller.front_controller.M2_controller.current_speed);
            Serial.print(" ");
            Serial.print(controller.rear_controller.M1_controller.current_speed);
            Serial.print(" ");
            Serial.println(controller.rear_controller.M2_controller.current_speed);
        }

        delay(10);
        for(auto& sensor : VL53L1XExtended::sensors)
        {
            sensor.clearInterrupt();        
        }
        indicator.refresh(current_time);

        // Serial.print("MAIN LOOP POINTER ");
        // Serial.println((int) next_task.get());
        // if (next_task.use_count() > 0)
        // {
        //     if(logging)
        //     {
        //         Serial.println("NEXT TASK EXISTS");
        //         Serial.print("USE COUNT ");
        //         Serial.println(next_task.use_count());
        //     }
        //     current_task.swap(next_task);
        //     // next_task = nullptr;
        // }
    }
}