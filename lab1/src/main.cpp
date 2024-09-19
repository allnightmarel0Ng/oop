#include <iostream>
#include "balance.h"

int main()
{
    std::string input;
    std::cin >> input;
    try
    {
        auto isBalanced = IsBalancedParentheses(input);
        std::cout << std::boolalpha << isBalanced << std::endl;
    }
    catch (const std::invalid_argument &exception)
    {
        std::cerr << exception.what() << std::endl;
    }
    return 0;
}