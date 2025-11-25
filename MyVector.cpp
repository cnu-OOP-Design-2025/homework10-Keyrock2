#include <stdexcept>

template <typename T>
void MyVector<T>::push_back(const T &val)
{
    if (length == cap)
    {
        // 용량이 꽉 찼을 때 확장 (기본 1, 그 외 2배)
        size_t new_cap = (cap == 0) ? 1 : cap * 2;
        T *new_data = new T[new_cap];

        // 데이터 복사
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

template <typename T>
void MyVector<T>::pop_back()
{
    if (length > 0)
    {
        length--;
    }
}

template <typename T>
size_t MyVector<T>::size() const
{
    return length;
}

template <typename T>
size_t MyVector<T>::capacity() const
{
    return cap;
}

template <typename T>
bool MyVector<T>::empty() const
{
    return length == 0;
}

template <typename T>
T &MyVector<T>::operator[](int i)
{
    return data[i];
}

template <typename T>
T &MyVector<T>::at(size_t i)
{
    if (i >= length)
    {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

template <typename T>
T &MyVector<T>::front()
{
    return data[0];
}

template <typename T>
T &MyVector<T>::back()
{
    return data[length - 1];
}

template <typename T>
void MyVector<T>::clear()
{
    length = 0;
}

template <typename T>
bool MyVector<T>::operator==(const MyVector &other) const
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

template <typename T>
bool MyVector<T>::operator!=(const MyVector &other) const
{
    return !(*this == other);
}

template <typename T>
bool MyVector<T>::operator<(const MyVector &other) const
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

template <typename T>
bool MyVector<T>::operator>(const MyVector &other) const
{
    return other < *this;
}

template <typename T>
bool MyVector<T>::operator<=(const MyVector &other) const
{
    return !(*this > other);
}

template <typename T>
bool MyVector<T>::operator>=(const MyVector &other) const
{
    return !(*this < other);
}

// Iterator 구현

template <typename T>
T &MyVector<T>::Iterator::operator*()
{
    return *ptr;
}

template <typename T>
typename MyVector<T>::Iterator &MyVector<T>::Iterator::operator++()
{
    ++ptr;
    return *this;
}

template <typename T>
typename MyVector<T>::Iterator &MyVector<T>::Iterator::operator--()
{
    --ptr;
    return *this;
}

template <typename T>
typename MyVector<T>::Iterator MyVector<T>::Iterator::operator+(int n) const
{
    return Iterator(ptr + n);
}

template <typename T>
typename MyVector<T>::Iterator MyVector<T>::Iterator::operator-(int n) const
{
    return Iterator(ptr - n);
}

template <typename T>
bool MyVector<T>::Iterator::operator==(const Iterator &other) const
{
    return ptr == other.ptr;
}

template <typename T>
bool MyVector<T>::Iterator::operator!=(const Iterator &other) const
{
    return ptr != other.ptr;
}

template <typename T>
int MyVector<T>::Iterator::operator-(const Iterator &other) const
{
    return ptr - other.ptr;
}

// Iterator 관련 MyVector 함수 구현

template <typename T>
typename MyVector<T>::Iterator MyVector<T>::begin()
{
    return Iterator(data);
}

template <typename T>
typename MyVector<T>::Iterator MyVector<T>::end()
{
    return Iterator(data + length);
}

template <typename T>
typename MyVector<T>::Iterator MyVector<T>::insert(Iterator pos, const T &value)
{
    // 현재 위치의 인덱스 계산
    long long index = pos - begin();

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

    // 뒤쪽 요소들을 한 칸씩 뒤로 이동
    for (long long i = length; i > index; --i)
    {
        data[i] = data[i - 1];
    }

    data[index] = value;
    length++;

    return Iterator(data + index);
}

template <typename T>
typename MyVector<T>::Iterator MyVector<T>::erase(Iterator pos)
{
    long long index = pos - begin();

    // 뒤쪽 요소들을 한 칸씩 앞으로 이동
    for (size_t i = index; i < length - 1; ++i)
    {
        data[i] = data[i + 1];
    }

    length--;
    return Iterator(data + index);
}