#include "trapezoid.h"

Trapezoid::Trapezoid(
    const Point &p1, 
    const Point &p2, 
    const Point &p3, 
    const Point &p4):
    _points({p1, p2, p3, p4})
{
    if (!validate())
    {
        throw std::invalid_argument("Not a trapezoid points");
    }
}

Point Trapezoid::Center() const noexcept
{
    double cx = 0, cy = 0;
    for (const auto &p: _points) 
    {
        cx += p.x;
        cy += p.y;
    }
    return Point(cx / 4, cy / 4);
}

Trapezoid::operator double() const noexcept
{
    return 0.5 * (_points[0].distance(_points[3]) + _points[1].distance(_points[2])) * std::abs(_points[2].y - _points[0].y);
}

bool Trapezoid::operator==(const Trapezoid &other) const noexcept
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

bool Trapezoid::operator!=(const Trapezoid &other) const noexcept
{
    return !(*this == other);
}

std::ostream &operator<<(std::ostream &os, const Trapezoid &trapezoid)
{
    os << trapezoid._points[0] << " " << trapezoid._points[1] << " " << trapezoid._points[2] << " " << trapezoid._points[3];
    return os;
}

std::istream &operator>>(std::istream &is, Trapezoid &trapezoid)
{
    is >> trapezoid._points[0] >> trapezoid._points[1] >> trapezoid._points[2] >> trapezoid._points[3];
    if (!trapezoid.validate())
    {
        throw std::invalid_argument("Not a valid trapezoid!");
    }

    return is;
}

double Trapezoid::slope(const Point &one, const Point &another) noexcept
{
    return one.x == another.x ? INFINITY : (another.y - one.y) / (another.x - one.x);
}

bool Trapezoid::validate() const noexcept
{
    std::array<double, 6> slopes;

    std::size_t index = 0;
    for (std::size_t i = 0; i < _points.size(); i++)
    {
        for (std::size_t j = i + 1; j < _points.size(); j++)
        {
            slopes[index++] = slope(_points[i], _points[j]);
        }
    }

    int parallelCount = 0;
    for (int i = 0; i < _points.size() + 2; ++i) 
    {
        for (int j = i + 1; j < _points.size() + 2; ++j) 
        {
            if (std::abs(slopes[i] - slopes[j]) < 1e-9) 
            {
                parallelCount++;
            }
        }
    }

    return parallelCount == 1;
}