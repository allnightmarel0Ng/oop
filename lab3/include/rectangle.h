#ifndef LAB3_RECTANGLE_H
#define LAB3_RECTANGLE_H

#include <array>

#include "figure.h"

class Rectangle final:
    public Figure
{
public:
    explicit Rectangle(
        const Point &p1 = Point(), 
        const Point &p2 = Point(), 
        const Point &p3 = Point(), 
        const Point &p4 = Point());

public:
    ~Rectangle() override = default;
    Rectangle(const Rectangle &other) = default;
    Rectangle &operator=(const Rectangle &other) = default;
    Rectangle(Rectangle &&other) = default;
    Rectangle &operator=(Rectangle &&other) = default;

public:
    [[nodiscard]] Point Center() const noexcept override;
    explicit operator double() const noexcept override;

public:
    bool operator==(const Rectangle &other) const noexcept;
    bool operator!=(const Rectangle &other) const noexcept;

public:
    friend std::ostream &operator<<(std::ostream &os, const Rectangle &rectangle);
    friend std::istream &operator>>(std::istream &is, Rectangle &rectangle);

private:
    bool validate() const noexcept;

private:
    std::array<Point, 4> _points;
};

#endif //LAB3_RECTANGLE_H
