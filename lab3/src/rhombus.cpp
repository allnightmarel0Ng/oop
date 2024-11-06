#include "rhombus.h"

Rhombus::Rhombus(
    const Point &p1,
    const Point &p2,
    const Point &p3,
    const Point &p4): 
    _points({p1, p2, p3, p4})
{
    if (!validate())
    {
        throw std::invalid_argument("Not a rhombus points");
    }
}

Point Rhombus::Center() const noexcept
{
    double cx = 0, cy = 0;
    for (const auto &p: _points)
    {
        cx += p.x;
        cy += p.y;
    }
    return Point(cx / 4, cy / 4);
}

Rhombus::operator double() const noexcept
{
    return 0.5 * _points[0].distance(_points[2]) * _points[1].distance(_points[3]);
}

bool Rhombus::operator==(const Rhombus &other) const noexcept
{
    for (int i = 0; i < _points.size(); ++i)
    {
        if (_points[i] != other._points[i])
        {
            return false;
        }
    }
    return true;
}

bool Rhombus::operator!=(const Rhombus &other) const noexcept
{
    return !(*this == other);
}

std::ostream &operator<<(std::ostream &os, const Rhombus &rhombus)
{
    os << rhombus._points[0] << " " << rhombus._points[1] << " " << rhombus._points[2] << " " << rhombus._points[3];
    return os;
}

std::istream &operator>>(std::istream &is, Rhombus &rhombus)
{
    is >> rhombus._points[0] >> rhombus._points[1] >> rhombus._points[2] >> rhombus._points[3];
    if (!rhombus.validate())
    {
        throw std::invalid_argument("Invalid rhombus");
    }
    return is;
}

double Rhombus::slope(const Point &one, const Point &another) noexcept
{
    return one.x == another.x ? INFINITY : (another.y - one.y) / (another.x - one.x);
}

bool Rhombus::validate() const noexcept
{
    auto slope1 = slope(_points[0], _points[1]);
    auto slope2 = slope(_points[2], _points[3]);
    auto slope3 = slope(_points[1], _points[2]);
    auto slope4 = slope(_points[3], _points[0]);

    return (slope1 == slope2 && slope3 == slope4);
}