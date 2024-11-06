#ifndef LAB4_FIGURE_H
#define LAB4_FIGURE_H

#include <iostream>
#include <memory>

#include "point.h"

template<typename T>
class Figure
{
public:
    Figure() = default;

public:
    virtual ~Figure() = default;

public:
    [[nodiscard]] virtual Point<T> Center() const noexcept = 0;
    virtual explicit operator double() const noexcept = 0;

};

#endif //LAB4_FIGURE_H
