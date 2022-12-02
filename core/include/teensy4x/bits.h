#ifndef bits_h
#define bits_h

typedef uint8_t byte;

constexpr uint8_t lowByte(uint16_t num)
{
    return num & 0xff;
}

constexpr uint8_t highByte(uint16_t num)
{
    return (num >> 8) & 0xff;
}

#endif
