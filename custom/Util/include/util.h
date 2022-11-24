#pragma once

namespace Util
{
    template <typename T, int N>
    class fifo_t
    {
    public:
        std::array<T, N> buffer;
        int size = 0;
        int last = 0;

        void push(const T& value);
        T& operator[](int index);
    };
} // namespace Util
