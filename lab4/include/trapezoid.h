#ifndef LAB4_TRAPEZOID_H
#define LAB4_TRAPEZOID_H

#include <array>

#include "figure.h"

template<typename T>
class Trapezoid final:
    public Figure<T>
{
public:
    explicit Trapezoid(
        const Point<T> &p1, 
        const Point<T> &p2, 
        const Point<T> &p3, 
        const Point<T> &p4);

public:
    ~Trapezoid() override = default;
    Trapezoid(const Trapezoid &other) = default;
    Trapezoid &operator=(const Trapezoid &other) = default;
    Trapezoid(Trapezoid &&other) = default;
    Trapezoid &operator=(Trapezoid &&other) = default;

public:
    [[nodiscard]] Point<T> Center() const noexcept override;
    explicit operator double() const noexcept override;

public:
    bool operator==(const Trapezoid &other) const noexcept;
    bool operator!=(const Trapezoid &other) const noexcept;

public:
    template<typename U>
    friend std::ostream &operator<<(std::ostream &os, const Trapezoid<U> &trapezoid);
    template<typename U>
    friend std::istream &operator>>(std::istream &is, Trapezoid<U> &trapezoid);


private:
    inline static double slope(const Point<T> &one, const Point<T> &another) noexcept;
    static bool validate(const std::array<Point<T>, 4> &points) noexcept;

private:
    std::array<Point<T>, 4> _points;
};

template<typename T>
Trapezoid<T>::Trapezoid(
    const Point<T> &p1, 
    const Point<T> &p2, 
    const Point<T> &p3, 
    const Point<T> &p4):
    _points({p1, p2, p3, p4})
{
    if (!validate(_points))
    {
        throw std::invalid_argument("Not a trapezoid points");
    }
}

template<typename T>
Point<T> Trapezoid<T>::Center() const noexcept
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
Trapezoid<T>::operator double() const noexcept
{
    return 0.5 * (_points[0].distance(_points[3]) + _points[1].distance(_points[2])) * std::abs(_points[2].y - _points[0].y);
}

template<typename T>
bool Trapezoid<T>::operator==(const Trapezoid &other) const noexcept
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
bool Trapezoid<T>::operator!=(const Trapezoid &other) const noexcept
{
    return !(*this == other);
}

template<typename U>
std::ostream &operator<<(std::ostream &os, const Trapezoid<U> &trapezoid)
{
    os << trapezoid._points[0] << " " << trapezoid._points[1] << " " << trapezoid._points[2] << " " << trapezoid._points[3];
    return os;
}

template<typename U>
std::istream &operator>>(std::istream &is, Trapezoid<U> &trapezoid)
{
    std::array<Point<U>, 4> newValues;
    
    is >> newValues[0] >> newValues[1] >> newValues[2] >> newValues[3];
    if (!trapezoid.validate(newValues))
    {
        throw std::invalid_argument("Not a valid trapezoid!");
    }

    trapezoid._points = newValues;

    return is;
}

template<typename T>
double Trapezoid<T>::slope(const Point<T> &one, const Point<T> &another) noexcept
{
    return one.x == another.x ? INFINITY : (another.y - one.y) / (another.x - one.x);
}

template<typename T>
bool Trapezoid<T>::validate(const std::array<Point<T>, 4> &points) noexcept
{
    std::array<double, 6> slopes;

    std::size_t index = 0;
    for (std::size_t i = 0; i < points.size(); i++)
    {
        for (std::size_t j = i + 1; j < points.size(); j++)
        {
            slopes[index++] = slope(points[i], points[j]);
        }
    }

    int parallelCount = 0;
    for (int i = 0; i < points.size() + 2; ++i) 
    {
        for (int j = i + 1; j < points.size() + 2; ++j) 
        {
            if (std::abs(slopes[i] - slopes[j]) < 1e-9) 
            {
                parallelCount++;
            }
        }
    }

    return parallelCount == 1;
}

#endif //LAB4_TRAPEZOID_H
