#include <iostream>
#include <cstdint>
#include <map>

#include "allocator.h"
#include "list.h"

int main()
{
    std::map<std::uint32_t, std::uint32_t, std::less<>, Allocator<std::pair<const std::uint32_t, std::uint32_t>>> factorials;

    factorials[0] = 1;
    for (std::uint32_t i = 1; i < 10; ++i)
    {
        factorials[i] = factorials[i - 1] * i;
    }

    for (const auto &[key, value]: factorials)
    {
        std::cout << key << " " << value << std::endl;
    }

    List<int> list;
    for (std::size_t i = 0; i < 15; ++i)
    {
        list.PushBack(i);
    }

    for (const auto &value: list)
    {
        std::cout << value << std::endl;
    }

    return 0;
}