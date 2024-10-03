#ifndef LAB5_LIST_H
#define LAB5_LIST_H

#include <iostream>

#include "allocator.h"

template<typename T, std::size_t BlockSize, typename Allocator = Allocator<T, BlockSize>>
class List
{
public:
    List();

};

#endif //LAB5_LIST_H
