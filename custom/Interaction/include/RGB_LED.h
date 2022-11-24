#pragma once
#include <core/core.h>

class RGB_LED
{
public:
    uint8_t R_pin;
    uint8_t G_pin;
    uint8_t B_pin;

    int R;
    int G;
    int B;

    int period_ms = 0;

    long on_start = 0;

    RGB_LED(uint8_t R_pin, uint8_t G_pin, uint8_t B_pin)
        : R_pin(R_pin), G_pin(G_pin), B_pin(B_pin)
    {
        pinMode(R_pin, OUTPUT);
        pinMode(G_pin, OUTPUT);
        pinMode(B_pin, OUTPUT);
    }

    void set_color(int R, int G, int B);

    void refresh(long current_time);
};