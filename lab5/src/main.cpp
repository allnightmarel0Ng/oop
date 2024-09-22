#include <iostream>
#include <cstdint>
#include <map>

#include <allocator.h>

std::uint32_t factorial(std::uint32_t value)
{
    if (value == 0 || value == 1)
    {
        return 1;
    }

    return value * factorial(value - 1);
}

int main()
{
    std::map<std::uint32_t, std::uint32_t, std::less<>, Allocator<std::pair<const std::uint32_t, std::uint32_t>, sizeof(std::pair<const std::uint32_t, std::uint32_t>)>> factorials;

    for (std::uint32_t i = 0; i < 10; ++i)
    {
        factorials[i] = factorial(i);
    }

    for (const auto &[key, value]: factorials)
    {
        std::cout << key << " " << value << std::endl;
    }

    return 0;
}