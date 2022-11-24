#include <util.h>

namespace Util
{
    template <typename T, int N>
    void fifo_t<T, N>::push(const T& value)
    {
        buffer[last] = value
        if(size < buffer.size())
        {
            ++size;
        }
        last = (last + 1) % size;
    }

    template <typename T, int N>
    T& fifo_t<T, N>::operator[](int index)
    {
        return buffer[(last + size + index) % size];
    }
} // namespace Util