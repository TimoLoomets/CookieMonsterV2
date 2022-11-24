#include <RGB_LED.h>
#include <algorithm>

void RGB_LED::set_color(int R_, int G_, int B_)
{
    R = std::clamp(R_, 0, 255);
    G = std::clamp(G_, 0, 255);
    B = std::clamp(B_, 0, 255);
    refresh(millis());
}

void RGB_LED::refresh(long current_time)
{
    if(current_time > on_start + period_ms
       && current_time < on_start + 2 * period_ms)
    {
        digitalWrite(R_pin, 0);
        digitalWrite(G_pin, 0);
        digitalWrite(B_pin, 0);
    }
    else
    {
        if (current_time > on_start + period_ms)
        {
            on_start = current_time;
        }
        digitalWrite(R_pin, R > 0);
        digitalWrite(G_pin, G > 0);
        digitalWrite(B_pin, B > 0);
    }
    
    // analogWrite(R_pin, R);
    // analogWrite(G_pin, G);
    // analogWrite(B_pin, B);

    // Serial.print("PINS: ");
    // Serial.print(R_pin);
    // Serial.print(" ");
    // Serial.print(G_pin);
    // Serial.print(" ");
    // Serial.println(B_pin);
    // Serial.print("SETTING COLOR: ");
    // Serial.print(R);
    // Serial.print(" ");
    // Serial.print(G);
    // Serial.print(" ");
    // Serial.println(B);
}