#ifndef LAB3_POINT_H
#define LAB3_POINT_H

#include <iostream>
#include <cmath>

struct Point final
{

public:
    explicit Point(double x, double y);

public:
    inline bool operator==(const Point &other) const noexcept;
    inline bool operator!=(const Point &other) const noexcept;

public:
    friend std::ostream &operator<<(std::ostream &os, const Point &point);
    friend std::istream &operator>>(std::istream &is, Point &point);

public:
    [[nodiscard]] double distance(const Point &other) const noexcept;

public:
    double x, y;

};

#endif //LAB3_POINT_H
