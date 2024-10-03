#include "point.h"

Point::Point(double x, double y):
    x(x), y(y)
{

}

std::ostream &operator<<(std::ostream &os, const Point &point)
{
    os << "(" << point.x << ", " << point.y << ")";
    return os;
}

bool Point::operator==(const Point &other) const noexcept
{
    return x == other.x && y == other.y;
}

bool Point::operator!=(const Point &other) const noexcept
{
    return !(*this == other);
}

std::istream &operator>>(std::istream &is, Point &point)
{
    double x, y;
    is >> x >> y;
    point.x = x;
    point.y = y;
    return is;
}

double Point::distance(const Point &other) const noexcept
{
    auto dx = x - other.y;
    auto dy = y - other.y;
    return std::sqrt(dx * dx + dy * dy);
}



