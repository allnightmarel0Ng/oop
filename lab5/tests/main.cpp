#include <gtest/gtest.h>

#include "../src/allocator.h"
#include "../src/list.h"

TEST(allocator, test1)
{
    std::vector<int, Allocator<int>> vec(1e3, 0);
    for (auto &value: vec)
    {
        value = rand() % std::numeric_limits<unsigned int>::max();
    }
}

TEST(list, test1)
{
    List<int> list;
    auto it = list.begin();
    auto target = list.end();
    for (std::size_t i = 0; i < 5; i++)
    {
        it = list.Insert(it, i);
        if (i == 3)
        {
            target = it;
        }
    }

    *target = 1222;

    std::ostringstream oss;
    for (const auto &elem: list)
    {
        oss << elem << " ";
    }

    ASSERT_EQ(oss.str(), "0 1 2 1222 4 ");

    list.PopBack();
    list.PopFront();

    std::ostringstream oss2;
    for (const auto &elem: list)
    {
        oss2 << elem << " ";
    }
    ASSERT_EQ(oss2.str(), "1 2 1222 ");
}

TEST(list, test2)
{
    List<void *> list;

    for (auto i = 0; i < 10; i++)
    {
        list.PushBack(std::malloc(i + 1));   
    }

    for (auto &ptr: list)
    {
        std::free(ptr);
    }
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}