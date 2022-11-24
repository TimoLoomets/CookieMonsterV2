#include <core/core.h>
#include <AckermannController.h>
#include <VL53L1X_extended.hpp>
#include <RGB_LED.h>
#include <navigation.hpp>
#include <memory>

#include <TeensyDebug.h>

int main()
{
    RGB_LED indicator(16, 15, 17);
    indicator.set_color(0, 0, 100);

    const int switch_pin = 6;
    pinMode(6, switch_pin);

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
        sensor.init();
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

    const bool logging = true;
    const bool move = true;

    std::shared_ptr<Task> next_task;
    std::shared_ptr<Task> current_task;

    current_task = std::make_shared<StraightTask>(&controller, indicator, next_task);
    current_task->logging = logging;

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
        if(current_task)
        {
            Serial.print("POINTER EXISTANCES: ");
            Serial.println(current_task.use_count());
            current_task->handle_task(current_time);
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
    }
}