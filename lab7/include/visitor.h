#ifndef LAB7_VISITOR_H
#define LAB7_VISITOR_H

#include <memory>
#include <cstdint>
#include <vector>

class NPC;
class Orc;
class Squirrel;
class Bear;

struct Cell
{
    enum class Type: std::uint8_t
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

class Visitor
{

public:
    explicit Visitor() = default;
    virtual ~Visitor() = default;

public:
    virtual void Visit(Orc &ref) noexcept = 0;
    virtual void Visit(Squirrel &ref) noexcept = 0;
    virtual void Visit(Bear &ref) noexcept = 0;

};

class Mover: 
    public Visitor
{

public:
    explicit Mover(std::vector<std::vector<Cell>> &field);

public:
    void Visit(Orc &ref) noexcept override;
    void Visit(Squirrel &ref) noexcept override;
    void Visit(Bear &ref) noexcept override;

private:
    void move(NPC *ptr, std::size_t &x, std::size_t &y);  

private:
    std::vector<std::vector<Cell>> &_field;

};

#endif