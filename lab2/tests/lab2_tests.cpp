#include <gtest/gtest.h>
#include "../src/octal.h"

TEST(tests, test1)
{
    std::ostringstream oss;
    oss << Octal("34532");
    ASSERT_EQ(oss.str(), "34532");
}

TEST(tests, test2)
{
    std::ostringstream oss;
    oss << Octal({0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7}) + Octal("34532");
    ASSERT_EQ(oss.str(), "1271321");
}

TEST(tests, test3)
{
    std::ostringstream oss;
    oss << Octal({3, 4, 5, 6, 7}) + Octal("74532");
    ASSERT_EQ(oss.str(), "131321");
}

TEST(tests, test4)
{
    ASSERT_THROW(Octal({3, 4, 5, 6, 7}) - Octal("74532"), std::invalid_argument);
}

TEST(tests, test5)
{
    std::ostringstream oss;
    oss << Octal("74532") - Octal({3, 4, 5, 6, 7});
    ASSERT_EQ(oss.str(), "37743");
}

TEST(tests, test6)
{
    ASSERT_THROW(Octal("345673453455675675675877"), std::invalid_argument);
}

TEST(tests, test7)
{
    ASSERT_TRUE(Octal("23012") != Octal("3234"));
}

TEST(tests, test8)
{
    ASSERT_TRUE(Octal("23012") > Octal("3234"));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}