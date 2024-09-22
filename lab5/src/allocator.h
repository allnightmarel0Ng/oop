#ifndef LAB5_ALLOCATOR_H
#define LAB5_ALLOCATOR_H

#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T, std::size_t BlockSize>
class Allocator
{

public:
    template <typename U>
    struct rebind {
        using other = Allocator<U, BlockSize>;
    };

public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = size_t;

public:
    Allocator();

public:
    pointer allocate(size_type size);
    void deallocate(pointer at, size_type size);

public:
    virtual ~Allocator();
    Allocator(const Allocator<value_type, BlockSize> &other);
    Allocator &operator=(const Allocator<value_type, BlockSize> &other);
    Allocator(Allocator<value_type, BlockSize> &&other) noexcept;
    Allocator& operator=(Allocator<value_type, BlockSize> &&other) noexcept;

private:
    void clear() noexcept;
    void copyFrom(const Allocator<value_type, BlockSize> &other);
    void moveFrom(Allocator<value_type, BlockSize> &&other) noexcept;

private:
    std::vector<std::pair<pointer, size_type>> _blocks;

};

template<typename T, std::size_t BlockSize>
Allocator<T, BlockSize>::Allocator()
{
    if (BlockSize == 0)
    {
        throw std::logic_error("Unable to allocate blocks of 0 size");
    }
}

template<typename T, std::size_t BlockSize>
typename Allocator<T, BlockSize>::pointer Allocator<T, BlockSize>::allocate(std::size_t size)
{
    auto result = new T[BlockSize * size];
    _blocks.push_back(std::make_pair(result, BlockSize * size));
    return result;
}

template<typename T, std::size_t BlockSize>
void Allocator<T, BlockSize>::deallocate(pointer at, std::size_t size)
{
    for (auto it = _blocks.begin(); it != _blocks.end(); ++it)
    {
        if (it->first == at)
        {
            delete[] it->first;
            _blocks.erase(it);
            break;
        }
    }
}

template<typename T, std::size_t BlockSize>
Allocator<T, BlockSize>::~Allocator()
{
    clear();
}

template<typename T, std::size_t BlockSize>
Allocator<T, BlockSize>::Allocator(const Allocator<T, BlockSize> &other)
{
    copyFrom(other);
}

template<typename T, std::size_t BlockSize>
Allocator<T, BlockSize> &Allocator<T, BlockSize>::operator=(const Allocator<T, BlockSize> &other)
{
    if (this != &other)
    {
        clear();
        copyFrom(other);
    }

    return *this;
}

template<typename T, std::size_t BlockSize>
Allocator<T, BlockSize>::Allocator(Allocator<T, BlockSize> &&other) noexcept
{
    moveFrom(std::move(other));
}

template<typename T, std::size_t BlockSize>
Allocator<T, BlockSize> &Allocator<T, BlockSize>::operator=(Allocator<T, BlockSize> &&other) noexcept
{
    if (this != &other)
    {
        clear();
        moveFrom(std::move(other));
    }

    return *this;
}

template<typename T, std::size_t BlockSize>
void Allocator<T, BlockSize>::clear() noexcept
{
    for (auto it = _blocks.begin(); it != _blocks.cend();)
    {
        delete[] it->first;
        it = _blocks.erase(it);
    }
}

template<typename T, std::size_t BlockSize>
void Allocator<T, BlockSize>::copyFrom(const Allocator<T, BlockSize> &other)
{
    for (const auto &block: other._blocks)
    {
        _blocks.push_back(std::make_pair(new T[block.second], block.second));
    }
}

template<typename T, std::size_t BlockSize>
void Allocator<T, BlockSize>::moveFrom(Allocator<T, BlockSize> &&other) noexcept
{
    _blocks = std::move(other._blocks);
}

#endif //LAB5_ALLOCATOR_H
