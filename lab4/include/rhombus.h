#ifndef LAB4_RHOMBUS_H
#define LAB4_RHOMBUS_H

#include <algorithm>
#include <array>

#include "figure.h"

template<typename T>
class Rhombus final:
    public Figure<T>
{
public:
    explicit Rhombus(
        const Point<T> &p1, 
        const Point<T> &p2, 
        const Point<T> &p3, 
        const Point<T> &p4);

public:
    ~Rhombus() override = default;
    Rhombus(const Rhombus &other) = default;
    Rhombus &operator=(const Rhombus &other) = default;
    Rhombus(Rhombus &&other) = default;
    Rhombus &operator=(Rhombus &&other) = default;

public:
    [[nodiscard]] Point<T> Center() const noexcept override;
    explicit operator double() const noexcept override;

public:
    bool operator==(const Rhombus &other) const noexcept;
    bool operator!=(const Rhombus &other) const noexcept;

public:
    template<typename U>
    friend std::ostream &operator<<(std::ostream &os, const Rhombus<U> &rhombus);
    template<typename U>
    friend std::istream &operator>>(std::istream &is, Rhombus<U> &rhombus);

private:
    static bool validate(const std::array<Point<T>, 4> &points) noexcept;

private:
    std::array<Point<T>, 4> _points;
};

template<typename T>
Rhombus<T>::Rhombus(
    const Point<T> &p1,
    const Point<T> &p2,
    const Point<T> &p3,
    const Point<T> &p4): 
    _points({p1, p2, p3, p4})
{
    if (!validate(_points))
    {
        throw std::invalid_argument("Not a rhombus points");
    }
}

template<typename T>
Point<T> Rhombus<T>::Center() const noexcept
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
Rhombus<T>::operator double() const noexcept
{
    return 0.5 * _points[0].distance(_points[2]) * _points[1].distance(_points[3]);
}

template<typename T>
bool Rhombus<T>::operator==(const Rhombus &other) const noexcept
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

template<typename T>
bool Rhombus<T>::operator!=(const Rhombus &other) const noexcept
{
    return !(*this == other);
}

template<typename U>
std::ostream &operator<<(std::ostream &os, const Rhombus<U> &rhombus)
{
    os << rhombus._points[0] << " " << rhombus._points[1] << " " << rhombus._points[2] << " " << rhombus._points[3];
    return os;
}

template<typename U>
std::istream &operator>>(std::istream &is, Rhombus<U> &rhombus)
{
    std::array<Point<U>, 4> newValues;
    is >> newValues[0] >> newValues[1] >> newValues[2] >> newValues[3];
    if (!rhombus.validate(newValues))
    {
        throw std::invalid_argument("Invalid rhombus");
    }
    rhombus._points = newValues;
    return is;
}

template<typename T>
bool Rhombus<T>::validate(const std::array<Point<T>, 4> &points) noexcept
{
    auto distance1 = points[0].distance(points[1]);
    auto distance2 = points[1].distance(points[2]);
    auto distance3 = points[2].distance(points[3]);
    auto distance4 = points[3].distance(points[0]);

    return distance1 == distance2 && distance2 == distance3 && distance3 == distance4 && distance4 == distance1;
}

#endif //LAB4_RHOMBUS_H