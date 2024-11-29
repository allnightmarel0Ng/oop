#ifndef LAB4_VECTOR_H
#define LAB4_VECTOR_H

#include <cstdlib>
#include <cstring>
#include <utility>

#include "figure.h"

template<typename T>
class Vector
{
public:
    explicit Vector(std::size_t size = 0, T defaultValue = T());

public:
    virtual ~Vector() = default;
    Vector(const Vector &other) = default;
    Vector &operator=(const Vector &other) = default;
    Vector(Vector &&other) noexcept = default;
    Vector &operator=(Vector &&other) noexcept = default;

public:
    bool IsEmpty() const noexcept;
    std::size_t Size() const noexcept;
    void PushBack(T &&value);
    void PopBack();
    T &operator[](std::size_t index) const;
    void Remove(std::size_t index);

private:
    std::shared_ptr<T []> _items;
    std::size_t _size;
    std::size_t _capacity;
};

template<typename T>
Vector<T>::Vector(std::size_t size, T defaultValue):
    _size(size),
    _capacity((size + 1) * 2)
{ 
    _items = std::shared_ptr<T []>(new T[_capacity]);
    for (std::size_t i = 0; i < size; i++)
    {
        _items[i] = std::move(defaultValue);
    }
}

template<typename T>
bool Vector<T>::IsEmpty() const noexcept 
{
    return _size == 0;
}

template<typename T>
std::size_t Vector<T>::Size() const noexcept
{
    return _size;
}

template<typename T>
void Vector<T>::PushBack(T &&value)
{
    _items[_size++] = std::forward<T>(value);

    if (_size == _capacity)
    {
        _capacity *= 2;
        std::shared_ptr<T []> tmp(new T[_capacity]);
        for (std::size_t i = 0; i < _size; i++)
        {
            tmp[i] = std::forward<T>(_items[i]);
        }
        _items = tmp;
    }
}

template<typename T>
void Vector<T>::PopBack()
{
    if (_size == 0)
    {
        throw std::runtime_error("No elements in vector");
    }

    _size--;
}

template<typename T>
T &Vector<T>::operator[](std::size_t index) const
{
    if (index >= _size)
    {
        throw std::out_of_range("Index out of range");
    }

    return _items[index];
}

template<typename T>
void Vector<T>::Remove(std::size_t index)
{
    if (index >= _size)
    {
        throw std::out_of_range("Index out of range");
    }

    for (auto i = index; i < _size - 1; i++)
    {
        _items[i] = std::forward<T>(_items[i + 1]);
    }

    PopBack();
}

#endif //LAB4_VECTOR_H