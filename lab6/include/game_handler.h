#ifndef LAB6_GAME_HANDLER_H
#define LAB6_GAME_HANDLER_H

#include <iostream>

#include "npc.h"
#include "observer.h"
#include "factory.h"

class GameHandler
{

public:
    explicit GameHandler() = delete;

public:
    static void Game(std::istream &is, std::ostream &os);

private:
    static void HandleAddNPC(std::istream &is, std::vector<std::vector<Cell>> &field);
    static void HandleLoadFile(const std::string &filepath, std::vector<std::vector<Cell>> &field);
    static void PrintObjects(std::ostream &os, const std::vector<std::vector<Cell>> &field) noexcept;
    static void HandleSaveFile(const std::string &filepath, const std::vector<std::vector<Cell>> &field) noexcept;
    static void HandleFight(const std::unique_ptr<Visitor> &visitor, std::vector<std::vector<Cell>> &field, std::size_t attackRange) noexcept;
    static void PrintMenu() noexcept;


};

#endif