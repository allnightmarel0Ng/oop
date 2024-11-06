#include "vector.h"

Vector::Vector():
    _size(0),
    _capacity(2),
    _items(static_cast<Figure **>(std::malloc(sizeof(Figure *) * _capacity)))
{
    if (_items == nullptr)
    {
        throw std::runtime_error("Allocation error");
    }
}

Vector::~Vector()
{
    clear();
}

Vector::Vector(const Vector &other)
{
    copy(other);
}

Vector &Vector::operator=(const Vector &other)
{
    if (this != &other)
    {
        clear();
        copy(other);
    }

    return *this;
}

Vector::Vector(Vector &&other) noexcept
{
    move(std::move(other));
}

Vector &Vector::operator=(Vector &&other) noexcept
{
    if (this != &other)
    {
        clear();
        move(std::move(other));
    }

    return *this;
}

bool Vector::IsEmpty() const noexcept 
{
    return _size == 0;
}

std::size_t Vector::Size() const noexcept
{
    return _size;
}

void Vector::PushBack(Figure *value)
{
    _items[_size++] = value;

    if (_size == _capacity)
    {
        _capacity *= 2;
        auto tmp = static_cast<Figure **>(std::realloc(_items, sizeof(Figure *) * _capacity));
        if (tmp == nullptr)
        {
            throw std::runtime_error("Allocation error");
        }

        _items = tmp;
    }
}

void Vector::PopBack()
{
    if (_size == 0)
    {
        throw std::runtime_error("No elements in vector");
    }

    _size--;
}

Figure *&Vector::operator[](std::size_t index) const
{
    if (index >= _size)
    {
        throw std::out_of_range("Index out of range");
    }

    return _items[index];
}

void Vector::Remove(std::size_t index)
{
    if (index >= _size)
    {
        throw std::out_of_range("Index out of range");
    }

    for (auto i = index; i < _size - 1; i++)
    {
        _items[i] = std::move(_items[i + 1]);
    }

    PopBack();
}

void Vector::clear() noexcept
{
    std::free(_items);
    _size = 0;
    _capacity = 0;
}

void Vector::copy(const Vector &other)
{
    _size = other._size;
    _capacity = other._capacity;
    _items = static_cast<Figure **>(std::malloc(sizeof(Figure *) * _capacity));
    std::memcpy(_items, other._items, sizeof(Figure *) * _size);
}

void Vector::move(Vector &&other) noexcept
{
    _size = other._size;
    _capacity = other._capacity;
    _items = std::exchange(other._items, nullptr); 
}