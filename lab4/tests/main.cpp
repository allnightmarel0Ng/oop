#include <gtest/gtest.h>

#include <rectangle.h>
#include <trapezoid.h>
#include <rhombus.h>
#include <vector.h>

TEST(vector, test1)
{
    Vector<int> vec;
    for (std::size_t i = 0; i < 1000; i++)
    {
        ASSERT_NO_THROW(vec.PushBack(rand() % (i + 1)));
    }

    vec.PopBack();
    ASSERT_EQ(vec.Size(), 999);
}

TEST(vector, test2)
{
    Vector<int> vec(100, 0);

    for (std::size_t i = 0; i < vec.Size(); i++)
    {
        vec[i] = i;
    }

    ASSERT_THROW(vec.Remove(253), std::out_of_range);
    ASSERT_NO_THROW(vec.Remove(45));

    bool found = false;
    for (std::size_t i = 0; i < vec.Size(); i++)
    {
        if (vec[i] == 45)
        {
            found = true;
        }
    }

    ASSERT_EQ(found, false);
}

TEST(io, rectangle)
{
    std::string in = "0 0 0 1 100 1 100 0";
    std::istringstream iss(in);

    Rectangle<double> r(Point(0., 0.), Point(0., 0.), Point(0., 0.), Point(0., 0.));
    ASSERT_NO_THROW(iss >> r);

    std::ostringstream oss;
    oss << r;
    ASSERT_EQ(oss.str(), "(0, 0) (0, 1) (100, 1) (100, 0)");
}

TEST(io, trapezoid)
{
    std::string in = "0. 0. 0. 2. 1. 1. 1. 0.";
    std::istringstream iss(in);

    Trapezoid<double> t(Point(0., 0.), Point(1., 1.), Point(2., 1.), Point(3., 0.));
    ASSERT_THROW(iss >> t, std::invalid_argument);

    std::ostringstream oss;
    oss << t;
    ASSERT_EQ(oss.str(), "(0, 0) (1, 1) (2, 1) (3, 0)");
}

TEST(io, rhombus)
{
    std::string in = "0 0 1 2 2 0 1 -2";
    std::istringstream iss(in);

    Rhombus<int> r(Point(0, 0), Point(1, 2), Point(2, 0), Point(1, -2));
    ASSERT_NO_THROW(iss >> r);

    std::string in2 = "0 0 0 1 -1 -1 200 200";
    std::istringstream iss2(in2);
    ASSERT_THROW(iss2 >> r, std::invalid_argument);

    std::ostringstream oss;
    oss << r;
    ASSERT_EQ(oss.str(), "(0, 0) (1, 2) (2, 0) (1, -2)");
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}