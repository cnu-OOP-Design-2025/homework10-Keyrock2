#pragma once

#include <initializer_list>
#include <cstddef>
#include <stdexcept> // std::out_of_range 사용을 위해 추가

template <typename T>
class MyVector
{
    T *data;       // 동적 배열을 가리키는 포인터
    size_t cap;    // 현재 할당된 배열 크기
    size_t length; // 실제 저장된 요소 개수
public:
    MyVector(std::initializer_list<T> init)
    {
        length = init.size();
        cap = length;
        data = new T[cap];
        size_t i = 0;
        for (const auto &val : init)
        {
            data[i++] = val;
        }
    }

    MyVector() : data(nullptr), length(0), cap(0) {}
    ~MyVector() { delete[] data; }

    // 멤버 함수 선언 및 구현 (헤더 내 통합)

    void push_back(const T &val)
    {
        if (length == cap)
        {
            size_t new_cap = (cap == 0) ? 1 : cap * 2;
            T *new_data = new T[new_cap];
            for (size_t i = 0; i < length; ++i)
            {
                new_data[i] = data[i];
            }
            delete[] data;
            data = new_data;
            cap = new_cap;
        }
        data[length++] = val;
    }

    void pop_back()
    {
        if (length > 0)
            length--;
    }

    size_t size() const { return length; }
    size_t capacity() const { return cap; }
    bool empty() const { return length == 0; }

    T &operator[](int i) { return data[i]; }

    T &at(size_t i)
    {
        if (i >= length)
            throw std::out_of_range("Index out of range");
        return data[i];
    }

    T &front() { return data[0]; }
    T &back() { return data[length - 1]; }

    void clear() { length = 0; }

    // 비교 연산자 구현
    bool operator==(const MyVector &other) const
    {
        if (length != other.length)
            return false;
        for (size_t i = 0; i < length; ++i)
        {
            if (data[i] != other.data[i])
                return false;
        }
        return true;
    }

    bool operator!=(const MyVector &other) const { return !(*this == other); }

    bool operator<(const MyVector &other) const
    {
        size_t len = (length < other.length) ? length : other.length;
        for (size_t i = 0; i < len; ++i)
        {
            if (data[i] < other.data[i])
                return true;
            if (data[i] > other.data[i])
                return false;
        }
        return length < other.length;
    }

    bool operator>(const MyVector &other) const { return other < *this; }
    bool operator<=(const MyVector &other) const { return !(*this > other); }
    bool operator>=(const MyVector &other) const { return !(*this < other); }

    // Iterator 클래스 정의 및 구현
    class Iterator
    {
        T *ptr;

    public:
        Iterator(T *p = nullptr) : ptr(p) {}

        T &operator*() { return *ptr; }

        Iterator &operator++()
        {
            ++ptr;
            return *this;
        }
        Iterator &operator--()
        {
            --ptr;
            return *this;
        }

        Iterator operator+(int n) const { return Iterator(ptr + n); }
        Iterator operator-(int n) const { return Iterator(ptr - n); }

        bool operator==(const Iterator &other) const { return ptr == other.ptr; }
        bool operator!=(const Iterator &other) const { return ptr != other.ptr; }

        int operator-(const Iterator &other) const { return ptr - other.ptr; }
    };

    // Iterator 관련 함수 구현
    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + length); }

    Iterator insert(Iterator pos, const T &value)
    {
        long long index = pos - begin();

        if (length == cap)
        {
            size_t new_cap = (cap == 0) ? 1 : cap * 2;
            T *new_data = new T[new_cap];
            for (size_t i = 0; i < length; ++i)
                new_data[i] = data[i];
            delete[] data;
            data = new_data;
            cap = new_cap;
        }

        for (long long i = length; i > index; --i)
        {
            data[i] = data[i - 1];
        }
        data[index] = value;
        length++;
        return Iterator(data + index);
    }

    Iterator erase(Iterator pos)
    {
        long long index = pos - begin();
        for (size_t i = index; i < length - 1; ++i)
        {
            data[i] = data[i + 1];
        }
        length--;
        return Iterator(data + index);
    }
};