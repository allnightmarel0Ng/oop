#include "../include/rectangle.h"

Rectangle::Rectangle(
    const Point &p1, 
    const Point &p2, 
    const Point &p3, 
    const Point &p4):
    _points({p1, p2, p3, p4})
{
    if (!validate())
    {
        throw std::invalid_argument("Invalid rectangle points");
    }
}

Point Rectangle::Center() const noexcept
{
    double cx = 0, cy = 0;
    for (const auto &p: _points) 
    {
        cx += p.x;
        cy += p.y;
    }
    return Point(cx / 4, cy / 4);
}

Rectangle::operator double() const noexcept
{
    return _points[0].distance(_points[1]) * _points[1].distance(_points[2]);
}

bool Rectangle::operator==(const Rectangle &other) const noexcept
{
    for (std::size_t i = 0; i < 4; i++)
    {
        if (_points[i] != other._points[i])
        {
            return false;
        }
    }

    return true;
}

bool Rectangle::operator!=(const Rectangle &other) const noexcept
{
    return !(*this == other);
}

std::ostream &operator<<(std::ostream &os, const Rectangle &rectangle)
{
    os << rectangle._points[0] << " " << rectangle._points[1] << " " << rectangle._points[2] << " " << rectangle._points[3];
    return os;
}

std::istream &operator>>(std::istream &is, Rectangle &rectangle)
{
    for (std::size_t i = 0; i < 4; i++)
    {
        is >> rectangle._points[i];
    }

    if (!rectangle.validate())
    {
        throw std::invalid_argument("Not a rectangle points");
    }
    return is;
}

bool Rectangle::validate() const noexcept
{
    for (std::size_t i = 1; i < _points.size(); i++)
    {
        if (_points[i].x != _points[i - 1].x && _points[i].y != _points[i - 1].y)
        {
            return false;
        }
    }

    return true;
}
