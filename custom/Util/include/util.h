#pragma once
#include <array>
#include <cmath>

namespace Util
{
    const double DEG2RAD = M_PI / 180;

    template <typename T, int N>
    class fifo_t
    {
    public:
        std::array<T, N> buffer;
        int size = 0;
        int last = 0;

        void push(const T& value)
        {
            buffer[last] = value;
            if(size < buffer.size())
            {
                ++size;
            }
            last = (last + 1) % size;
        }

        T& operator[](int index)
        {
            return buffer[(last + size + index) % size];
        }

        bool is_full()
        {
            return size == buffer.size();
        }
    };
} // namespace Util
