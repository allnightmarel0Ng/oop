#ifndef LAB3_TRAPEZOID_H
#define LAB3_TRAPEZOID_H

#include <array>

#include "figure.h"

class Trapezoid final:
    public Figure
{
public:
    explicit Trapezoid();

public:
    ~Trapezoid() override = default;
    Trapezoid(const Trapezoid &other) = default;
    Trapezoid &operator=(const Trapezoid &other) = default;
    Trapezoid(Trapezoid &&other) = default;
    Trapezoid &operator=(Trapezoid &&other) = default;

public:
    [[nodiscard]] Point center() const noexcept override;
    explicit operator double() const noexcept override;

public:
    bool operator==(const Trapezoid &other) const noexcept;
    bool operator!=(const Trapezoid &other) const noexcept;

public:
    friend std::ostream &operator<<(std::ostream &os, const Trapezoid &trapezoid);
    friend std::istream &operator>>(std::istream &is, Trapezoid &trapezoid);

private:
    std::array<Point, 4> _points;
};

#endif //LAB3_TRAPEZOID_H
