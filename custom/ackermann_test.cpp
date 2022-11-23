#pragma GCC optimize ("O0")

#include <core/core.h>
#include <AckermannController.h>
#include <TeensyDebug.h>




int main()
{   
    Serial.begin(9600);

    CookieMonsterDrive::AckermannController controller{{{7, 25, 8, 24}, {3, 2, -1}, {4, 5, 1}}
                                                 , {{39, 23, 40, 22}, {34, 41, -1}, {32, 33, 1}}
                                                 , {0, 60, 135}};

CookieMonsterDrive::AxleController rear_axle{{40, 22, 39, 23}, {32, 33}, {34, 41, -1}};
CookieMonsterDrive::AxleController front_axle{{7, 25, 8, 24}, {2, 3, -1}, {5, 4}};
    //debug.begin(Serial);
    //halt_cpu();
    //Serial.println("CODE START");

    // pinMode(7, OUTPUT);
    // pinMode(25, OUTPUT);
    // pinMode(8, OUTPUT);
    // pinMode(24, OUTPUT);
    // controller.front_controller.motor_controller.initialized=true;

    const long test_duration_millis = 3000;
    int test_count = 0;

    while(1)
    {
        Serial.print("Tests: ");
        Serial.println(test_count);
        Serial.println("Straight test");
        
        controller.speed = 0.5;
        controller.turn_rate = 0;
        
        // rear_axle.M1_controller.target_speed = 0.5;
        // rear_axle.M2_controller.target_speed = 0.5;
        long test_start = millis();
        long current_time = millis();
        while(current_time - test_start < test_duration_millis)
        {
            // rear_axle.update(current_time);
            // controller.rear_controller.motor_controller.setM1Speed(100);
            // controller.rear_controller.motor_controller.setM2Speed(100);
            // controller.front_controller.M1_controller.target_speed = 0.5;
            controller.update(current_time);
            // controller.update(current_time, true);
            
            
            delay(10);
            current_time = millis();
            Serial.print("Duration: ");
            Serial.print(millis() - test_start);
            Serial.print("/");
            Serial.println(test_duration_millis);
        }
        test_count++;

        controller.speed = 0;
        controller.turn_rate = 0;
        controller.update(millis(), true);

        delay(3000);

        
        Serial.println("Turn test");
        controller.speed = 0.5;
        controller.turn_rate = 1;
        test_start = millis();
        while(millis() - test_start < test_duration_millis)
        {
            controller.update(millis(), true);
            delay(10);
        }

        controller.speed = 0;
        controller.turn_rate = 0;
        controller.update(millis(), true);

        delay(3000);
        
    }
}