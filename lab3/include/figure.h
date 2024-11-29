#ifndef LAB3_FIGURE_H
#define LAB3_FIGURE_H

#include <iostream>

#include "point.h"

class Figure
{
public:
    Figure() = default;

public:
    virtual ~Figure() = default;

public:
    [[nodiscard]] virtual Point Center() const noexcept = 0;
    virtual explicit operator double() const noexcept = 0;

};

#endif //LAB3_FIGURE_H
