#ifndef LAB7_GAME_HANDLER_H
#define LAB7_GAME_HANDLER_H

#include <sstream>
#include <iostream>

#include "fighter.h"
#include "factory.h"

class GameHandler
{
    using Field = std::vector<std::vector<Cell>>;

public:
    explicit GameHandler() = delete;

public:
    static void Game(std::size_t size);
};


#endif