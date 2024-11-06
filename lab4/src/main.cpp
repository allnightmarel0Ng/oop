#include <iostream>

#include "figure.h"
#include "rhombus.h"
#include "rectangle.h"
#include "trapezoid.h"
#include "vector.h"

int main()
{
    try
    {
        std::unique_ptr<Rhombus<double>> rhombus = std::make_unique<Rhombus<double>>(
            Point(0.0, 0.0),
            Point(0.0, 0.0),
            Point(0.0, 0.0),
            Point(0.0, 0.0)
        );
        std::unique_ptr<Rectangle<double>> rectangle = std::make_unique<Rectangle<double>>(
            Point(0.0, 0.0),
            Point(0.0, 0.0),
            Point(0.0, 0.0),
            Point(0.0, 0.0)
        );
        std::unique_ptr<Trapezoid<double>> trapezoid = std::make_unique<Trapezoid<double>>(
            Point(0.0, 0.0),
            Point(0.1, 0.1),
            Point(0.2, 0.1),
            Point(0.2, 0.0)
        );;

        std::cin >> *rhombus >> *rectangle >> *trapezoid;

        Vector<std::unique_ptr<Figure<double>>> array;

        array.PushBack(std::move(rhombus));
        array.PushBack(std::move(rectangle));
        array.PushBack(std::move(trapezoid));

        for (std::size_t i = 0; i < array.Size(); ++i)
        {
            std::cout << "Geometric center of figure " << i + 1 << ": " << array[i]->Center() << std::endl;
            std::cout << "Area of figure " << i + 1 << ": " << static_cast<double>(*array[i]) << std::endl; 
        }
    }
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }

    return 0;
}