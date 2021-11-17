#pragma once


#include <assert.h>

template <class T1, class T2>
class Array
{
private:
    int m_length;
    T1* m_key;
    T2* m_data;

public:
    Array() : m_length{ 0 }, m_key{ nullptr }, m_data{ nullptr } {}

    Array(int length) : m_key{ new T1[length] }, m_data{ new T2[length] }, m_length{ length }{}

    Array(const Array& fromArray)
        : m_length{ fromArray.m_length },
          m_key{ fromArray.m_key },
          m_data{ fromArray.m_data }
    {
    }

    Array(Array&& fromArray) 
        : m_length{ fromArray.m_length }, 
          m_key{ fromArray.m_key }, 
          m_data{ fromArray.m_data }
    {
        fromArray.m_data = nullptr;
        fromArray.m_key = nullptr;
        fromArray.m_length = 0;
    }

    ~Array() { delete[] m_key; delete[] m_data; }
   
    Array& setDict(int index, const T1& key, const T2& data) 
    {
        m_key[index] = key;
        m_data[index] = data;
        return *this;
    }


    Array& operator=(const Array& fromArray) 
    {
        if (this == &fromArray)
            return *this;

        delete[] m_key;
        delete[] m_data;
        m_key = fromArray.m_key;
        m_data = fromArray.m_data;
        m_length = fromArray.m_length;
    }

    Array& operator=(Array&& fromArray) noexcept
    {
        if (this == &fromArray)
            return *this;
        std::swap(m_key, fromArray.m_key);
        std::swap(m_data, fromArray.m_data);
        delete[] m_key;
        delete[] m_data;
        m_key = fromArray.m_key;
        fromArray.m_key = nullptr;
        m_data = fromArray.m_data;
        fromArray.m_data = nullptr;
        m_length = fromArray.m_length;
        fromArray.m_length = 0;
    }

    T2& operator[](const T1& key)
    {
        for (int iii = 0; iii < m_length; ++iii)
            if (m_key[iii] == key) return m_data[iii];
        return m_data[0];
    }

    T1& operator[](const T2& data)
    {
        for (int iii = 0; iii < m_length; ++iii)
            if (m_data[iii] == data) return m_key[iii];
        return m_key[0];
    }

    int getLength(); // шаблонный метод
};

template <typename T1, typename T2> 
int Array<T1,T2>::getLength() { return m_length; } 
