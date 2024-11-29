#ifndef LAB6_OBSERVER_H
#define LAB6_OBSERVER_H

#include <iostream>
#include <memory>
#include <fstream>

class NPC;
class Orc;
class Squirrel;
class Bear;

struct Cell
{
    enum class Type
    {
        Orc,
        Squirrel,
        Bear,
        Empty
    };

    Type CellType;
    std::shared_ptr<NPC> Object;

    Cell(Cell::Type type = Cell::Type::Empty, std::shared_ptr<NPC> &&object = nullptr);
};

class Observer
{

public:
    virtual void HandleEvent(const Cell &killer, const Cell &victim) noexcept = 0;

protected:
    static inline std::string CellTypeToString(Cell::Type type) noexcept;
};

class FileLogger: 
    public Observer
{

public:
    explicit FileLogger() = default;

public:
    void HandleEvent(const Cell &killer, const Cell &victim) noexcept override;

private:
    std::ofstream ofs = std::ofstream("logs.txt", std::ios::out);
};

class ConsoleLogger: 
    public Observer
{

public:
    explicit ConsoleLogger() = default;

public:
    void HandleEvent(const Cell &killer, const Cell &victim) noexcept override;
};

#endif