#pragma once
#include <cstdint>

using IDType = std::uint64_t;

template <class T>
class TypeIDGenerator
{
public:
    template <class U>
    static IDType GenerateNewID()
    {
        m_id_counter++;
        static IDType counter = m_id_counter;
        return counter;
    }
private:
    static IDType m_id_counter;
};
template<class T> IDType TypeIDGenerator<T>::m_id_counter = 0;
