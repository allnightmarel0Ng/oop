#include <iostream>

#include <figure.h>
#include <rhombus.h>
#include <rectangle.h>
#include <trapezoid.h>
#include <vector.h>

int main()
{
    Rhombus rhombus;
    Rectangle rectangle;
    Trapezoid trapezoid(Point(0, 0), Point(1, 1), Point(2, 1), Point(3, 0));

    std::cin >> rhombus >> rectangle >> trapezoid;

    Vector array;

    array.PushBack(&rhombus);
    array.PushBack(&rectangle);
    array.PushBack(&trapezoid);

    for (std::size_t i = 0; i < array.Size(); ++i)
    {
        std::cout << "Geometric center of figure " << i + 1 << ": " << array[i]->Center() << std::endl;
        std::cout << "Area of figure " << i + 1 << ": " << static_cast<double>(*array[i]) << std::endl; 
    }

    return 0;
}