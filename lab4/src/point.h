#ifndef LAB4_POINT_H
#define LAB4_POINT_H

#include <iostream>
#include <cmath>

template<typename T>
struct Point final
{

public:
    explicit Point(const T &x = T(), const T &y = T());

public:
    bool operator==(const Point &other) const noexcept;
    bool operator!=(const Point &other) const noexcept;

public:
    template<typename U>
    friend std::ostream &operator<<(std::ostream &os, const Point<U> &point);
    template<typename U>
    friend std::istream &operator>>(std::istream &is, Point<U> &point);

public:
    [[nodiscard]] double distance(const Point &other) const noexcept;

public:
    T x, y;

};

template<typename T>
Point<T>::Point(const T &x, const T &y):
    x(x), y(y)
{

}

template<typename T>
bool Point<T>::operator==(const Point &other) const noexcept
{
    return x == other.x && y == other.y;
}

template<typename T>
bool Point<T>::operator!=(const Point &other) const noexcept
{
    return !(*this == other);
}

template<typename U>
std::ostream &operator<<(std::ostream &os, const Point<U> &point)
{
    os << "(" << point.x << ", " << point.y << ")";
    return os;
}

template<typename U>
std::istream &operator>>(std::istream &is, Point<U> &point)
{
    U x, y;
    is >> x >> y;
    point.x = x;
    point.y = y;
    return is;
}

template<typename T>
double Point<T>::distance(const Point &other) const noexcept
{
    auto dx = x - other.x;
    auto dy = y - other.y;
    return std::sqrt(dx * dx + dy * dy);
}

#endif //LAB4_POINT_H
