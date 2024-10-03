#include "rectangle.h"

Rectangle::Rectangle():
    _points({
        Point(0., 0.),
        Point(1., 0.),
        Point(0., 1.),
        Point(1., 1.),
    })
{

}

Point Rectangle::center() const noexcept
{
    auto minX = _points[0].x;
    auto maxX = _points[0].x;
    auto minY = _points[0].y;
    auto maxY = _points[0].y;

    for (const auto &point : _points)
    {
        if (point.x < minX) minX = point.x;
        if (point.x > maxX) maxX = point.x;
        if (point.y < minY) minY = point.y;
        if (point.y > maxY) maxY = point.y;
    }

    return Point((minX + maxX) / 2.0, (minY + maxY) / 2.0);
}

Rectangle::operator double() const noexcept
{
    return _points[0].distance(_points[1]) * _points[0].distance(_points[3]);
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
        if (i > 0)
        {
            if (rectangle._points[i] == rectangle._points[i - 1] ||
            (rectangle._points[i].x != rectangle._points[i - 1].x && rectangle._points[i].y != rectangle._points[i - 1].y))
            {
                throw std::invalid_argument("Not a rectangle points");
            }
        }
    }
    return is;
}


