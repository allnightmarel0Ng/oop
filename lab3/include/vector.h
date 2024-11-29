#ifndef LAB3_VECTOR_H
#define LAB3_VECTOR_H

#include <cstdlib>
#include <cstring>
#include <utility>

#include "figure.h"

class Vector
{

public:
    explicit Vector();

public:
    virtual ~Vector();
    Vector(const Vector &other);
    Vector &operator=(const Vector &other);
    Vector(Vector &&other) noexcept;
    Vector &operator=(Vector &&other) noexcept;

public:
    bool IsEmpty() const noexcept;
    std::size_t Size() const noexcept;
    void PushBack(Figure *value);
    void PopBack();
    Figure *&operator[](std::size_t index) const;
    void Remove(std::size_t index);

private:
    void clear() noexcept;
    void copy(const Vector &other);
    void move(Vector &&other) noexcept;

private:
    Figure **_items;
    std::size_t _size;
    std::size_t _capacity;
};

#endif