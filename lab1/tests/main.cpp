#include <gtest/gtest.h>

#include <balance.h>

TEST(positiveTests, test1)
{
    ASSERT_TRUE(IsBalancedParentheses("()"));
}

TEST(positiveTests, test2)
{
    ASSERT_TRUE(IsBalancedParentheses("(())((()())())"));
}

TEST(positiveTests, test3)
{
    ASSERT_THROW(IsBalancedParentheses("ghdjkgfhdjkfghejhtjkdlghdgd"), std::invalid_argument);
}

TEST(positiveTests, test4)
{
    ASSERT_THROW(IsBalancedParentheses("(((((((((((((((((((((((((((((((((((((((((((((((((())))))))))))))))))))))))))))))))))))))))))))))))))()"), std::invalid_argument);
}

TEST(negativeTests, test1)
{
    ASSERT_FALSE(IsBalancedParentheses(")(()))"));
}

TEST(negativeTests, test2)
{
    ASSERT_FALSE(IsBalancedParentheses(")"));
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}