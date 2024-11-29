#ifndef LAB4_RECTANGLE_H
#define LAB4_RECTANGLE_H

#include <array>

#include "figure.h"

template<typename T>
class Rectangle final:
    public Figure<T>
{
public:
    explicit Rectangle(
        const Point<T> &p1, 
        const Point<T> &p2, 
        const Point<T> &p3, 
        const Point<T> &p4);

public:
    ~Rectangle() override = default;
    Rectangle(const Rectangle &other) = default;
    Rectangle &operator=(const Rectangle &other) = default;
    Rectangle(Rectangle &&other) = default;
    Rectangle &operator=(Rectangle &&other) = default;

public:
    [[nodiscard]] Point<T> Center() const noexcept override;
    explicit operator double() const noexcept override;

public:
    bool operator==(const Rectangle &other) const noexcept;
    bool operator!=(const Rectangle &other) const noexcept;

public:
    template<typename U>
    friend std::ostream &operator<<(std::ostream &os, const Rectangle<U> &rectangle);
    template<typename U>
    friend std::istream &operator>>(std::istream &is, Rectangle<U> &rectangle);

private:
    static bool validate(const std::array<Point<T>, 4> &points) noexcept;

private:
    std::array<Point<T>, 4> _points;
};

template<typename T>
Rectangle<T>::Rectangle(
    const Point<T> &p1, 
    const Point<T> &p2, 
    const Point<T> &p3, 
    const Point<T> &p4):
    _points({p1, p2, p3, p4})
{
    if (!validate(_points))
    {
        throw std::invalid_argument("Invalid rectangle points");
    }
}

template<typename T>
Point<T> Rectangle<T>::Center() const noexcept
{
    T cx = 0, cy = 0;
    for (const auto &p: _points) 
    {
        cx += p.x;
        cy += p.y;
    }
    return Point<T>(cx / 4, cy / 4);
}

template<typename T>
Rectangle<T>::operator double() const noexcept
{
    return _points[0].distance(_points[1]) * _points[1].distance(_points[2]);
}

template<typename T>
bool Rectangle<T>::operator==(const Rectangle &other) const noexcept
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

template<typename T>
bool Rectangle<T>::operator!=(const Rectangle &other) const noexcept
{
    return !(*this == other);
}

template<typename U>
std::ostream &operator<<(std::ostream &os, const Rectangle<U> &rectangle)
{
    os << rectangle._points[0] << " " << rectangle._points[1] << " " << rectangle._points[2] << " " << rectangle._points[3];
    return os;
}

template<typename U>
std::istream &operator>>(std::istream &is, Rectangle<U> &rectangle)
{
    std::array<Point<U>, 4> newValues;
    for (std::size_t i = 0; i < 4; i++)
    {
        is >> newValues[i];
    }

    if (!rectangle.validate(newValues))
    {
        throw std::invalid_argument("Not a rectangle points");
    }

    rectangle._points = newValues;
    return is;
}

template<typename T>
bool Rectangle<T>::validate(const std::array<Point<T>, 4> &points) noexcept
{
    for (std::size_t i = 1; i < points.size(); i++)
    {
        if (points[i].x != points[i - 1].x && points[i].y != points[i - 1].y)
        {
            return false;
        }
    }

    return true;
}


#endif //LAB4_RECTANGLE_H
