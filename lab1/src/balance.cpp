#include "balance.h"

bool IsBalancedParentheses(const std::string &toCheck)
{
    if (toCheck.size() > 100)
    {
        throw std::invalid_argument("string size should be less or equal then 100");
    }

    int balance = 0;
    for (const auto &symbol: toCheck)
    {
        switch (symbol)
        {
            case '(':
               balance++;
               break;
            case ')':
               balance--;
               break;
            default:
               throw std::invalid_argument("string must only contain ( or )");
        }

        if (balance < 0)
        {
            return false;
        }
    }
    return balance == 0;
}