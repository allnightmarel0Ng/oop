#ifndef LAB3_RHOMBUS_H
#define LAB3_RHOMBUS_H

#include <algorithm>
#include <array>

#include "figure.h"

class Rhombus final:
    public Figure
{
public:
    explicit Rhombus(
        const Point &p1 = Point(), 
        const Point &p2 = Point(), 
        const Point &p3 = Point(), 
        const Point &p4 = Point());

public:
    ~Rhombus() override = default;
    Rhombus(const Rhombus &other) = default;
    Rhombus &operator=(const Rhombus &other) = default;
    Rhombus(Rhombus &&other) = default;
    Rhombus &operator=(Rhombus &&other) = default;

public:
    [[nodiscard]] Point Center() const noexcept override;
    explicit operator double() const noexcept override;

public:
    bool operator==(const Rhombus &other) const noexcept;
    bool operator!=(const Rhombus &other) const noexcept;

public:
    friend std::ostream &operator<<(std::ostream &os, const Rhombus &rhombus);
    friend std::istream &operator>>(std::istream &is, Rhombus &rhombus);

private:
    inline static double slope(const Point &one, const Point &another) noexcept;
    bool validate() const noexcept;

private:
    std::array<Point, 4> _points;
};

#endif