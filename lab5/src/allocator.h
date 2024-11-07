#ifndef LAB5_ALLOCATOR_H
#define LAB5_ALLOCATOR_H

#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
class Allocator
{

public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = size_t;

public:
    Allocator() = default;

public:
    pointer allocate(size_type size);
    void deallocate(pointer at, size_type size);

public:
    virtual ~Allocator();
    Allocator(const Allocator<value_type> &other);
    Allocator &operator=(const Allocator<value_type> &other);
    Allocator(Allocator<value_type> &&other) noexcept;
    Allocator& operator=(Allocator<value_type> &&other) noexcept;

private:
    void clear() noexcept;
    void copyFrom(const Allocator<value_type> &other);
    void moveFrom(Allocator<value_type> &&other) noexcept;

private:
    std::vector<std::pair<pointer, size_type>> _blocks;

};

template<typename T>
typename Allocator<T>::pointer Allocator<T>::allocate(std::size_t size)
{
    auto result = new T[size];
    _blocks.push_back(std::make_pair(result, size));
    return result;
}

template<typename T>
void Allocator<T>::deallocate(pointer at, std::size_t size)
{
    for (auto it = _blocks.begin(); it != _blocks.end(); ++it)
    {
        if (it->first == at && it->second == size)
        {
            delete[] it->first;
            _blocks.erase(it);
            break;
        }
    }
}

template<typename T>
Allocator<T>::~Allocator()
{
    clear();
}

template<typename T>
Allocator<T>::Allocator(const Allocator<T> &other)
{
    copyFrom(other);
}

template<typename T>
Allocator<T> &Allocator<T>::operator=(const Allocator<T> &other)
{
    if (this != &other)
    {
        clear();
        copyFrom(other);
    }

    return *this;
}

template<typename T>
Allocator<T>::Allocator(Allocator<T> &&other) noexcept
{
    moveFrom(std::move(other));
}

template<typename T>
Allocator<T> &Allocator<T>::operator=(Allocator<T> &&other) noexcept
{
    if (this != &other)
    {
        clear();
        moveFrom(std::move(other));
    }

    return *this;
}

template<typename T>
void Allocator<T>::clear() noexcept
{
    for (auto it = _blocks.begin(); it != _blocks.cend();)
    {
        delete[] it->first;
        it = _blocks.erase(it);
    }
}

template<typename T>
void Allocator<T>::copyFrom(const Allocator<T> &other)
{
    for (const auto &block: other._blocks)
    {
        _blocks.push_back(std::make_pair(new T[block.second], block.second));
    }
}

template<typename T>
void Allocator<T>::moveFrom(Allocator<T> &&other) noexcept
{
    _blocks = std::move(other._blocks);
}

#endif //LAB5_ALLOCATOR_H
