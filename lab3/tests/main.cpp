#include <gtest/gtest.h>

#include <figure.h>
#include <rhombus.h>
#include <rectangle.h>
#include <trapezoid.h>
#include <vector.h>

TEST(rhombus, ctor)
{
    ASSERT_NO_THROW(Rhombus(Point(0, 0), Point(1, 2), Point(2, 0), Point(1, -2)));

    ASSERT_THROW(
        Rhombus(Point(0, 1), Point(1, 222), Point(2, 123123), Point(-1, 2)), 
        std::invalid_argument);
}

TEST(rhombus, center)
{
    ASSERT_EQ(
        Rhombus(Point(0, 0), Point(1, 2), Point(2, 0), Point(1, -2)).Center(), 
        Point(1., 0.));
}

TEST(rhombus, area)
{
    ASSERT_EQ(
        static_cast<double>(Rhombus(Point(0, 0), Point(1, 2), Point(2, 0), Point(1, -2))), 
        4.);
}

TEST(rhombus, equality)
{
    ASSERT_EQ(
        Rhombus(Point(0, 0), Point(1, 2), Point(2, 0), Point(1, -2)),
        Rhombus(Point(0, 0), Point(1, 2), Point(2, 0), Point(1, -2)));
    
    ASSERT_NE(
        Rhombus(Point(0, 0), Point(0.5, 1), Point(1, 0), Point(0.5, -1)),
        Rhombus(Point(0, 0), Point(1, 2), Point(2, 0), Point(1, -2)));
}

TEST(rectangle, ctor)
{
    ASSERT_NO_THROW(Rectangle(Point(0, 0), Point(0, 1), Point(100, 1), Point(100, 0)));

    ASSERT_THROW(
        Rectangle(Point(0, 0), Point(1, 2), Point(2, 0), Point(1, -2)), 
        std::invalid_argument);
}

TEST(rectangle, center)
{
    ASSERT_EQ(
        Rectangle(Point(0, 0), Point(0, 1), Point(100, 1), Point(100, 0)).Center(), 
        Point(50., 0.5));
}

TEST(rectangle, area)
{
    ASSERT_DOUBLE_EQ(
        static_cast<double>(Rectangle(Point(0, 0), Point(0, 1), Point(100, 1), Point(100, 0))),
        100.);
}

TEST(rectangle, equality)
{
    ASSERT_EQ(
        Rectangle(Point(0, 0), Point(0, 1), Point(100, 1), Point(100, 0)),
        Rectangle(Point(0, 0), Point(0, 1), Point(100, 1), Point(100, 0)));

    ASSERT_NE(
        Rectangle(Point(0, 0), Point(0, 0.5), Point(50, 0.5), Point(50, 0)),
        Rectangle(Point(0, 0), Point(0, 1), Point(100, 1), Point(100, 0)));
}

TEST(trapezoid, ctor)
{
    ASSERT_NO_THROW(Trapezoid(Point(0, 0), Point(1, 1), Point(2, 1), Point(3, 0)));

    ASSERT_THROW(
        Trapezoid(Point(0, 0), Point(1, 1), Point(2, 1), Point(1, 0)),
        std::invalid_argument);
}

TEST(trapezoid, center)
{
    ASSERT_EQ(
        Trapezoid(Point(0, 0), Point(1, 1), Point(2, 1), Point(3, 0)).Center(),
        Point(1.5, 0.5));
}

TEST(trapezoid, area)
{
    ASSERT_DOUBLE_EQ(
        static_cast<double>(Trapezoid(Point(0, 0), Point(1, 1), Point(2, 1), Point(3, 0))),
        2.);
}

TEST(trapezoid, equality)
{
    ASSERT_EQ(
        Trapezoid(Point(0, 0), Point(1, 1), Point(2, 1), Point(3, 0)),
        Trapezoid(Point(0, 0), Point(1, 1), Point(2, 1), Point(3, 0)));

    ASSERT_NE(
        Trapezoid(Point(0, 0), Point(1, 1), Point(2, 1), Point(3, 0)),
        Trapezoid(Point(0, 0), Point(0.5, 0.5), Point(1, 0.5), Point(1.5, 0)));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}