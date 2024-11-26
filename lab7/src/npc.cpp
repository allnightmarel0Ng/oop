#include "common.h"

Cell::Cell(Cell::Type type, std::shared_ptr<NPC> &&object): 
    CellType(type), Object(std::move(object))
{

}

NPC::NPC(const std::string &name, std::size_t coordX, std::size_t coordY, std::size_t moveRange, std::size_t attackRange):
    _name(name), _place(coordX, coordY), _moveRange(moveRange), _attackRange(attackRange)
{
    
}

NPC::Point::Point(std::size_t x, std::size_t y):
    x(x), y(y)
{

}

Orc::Orc(const std::string &name, std::size_t coordX, std::size_t coordY):
    NPC(name, coordX, coordY, 20, 10)
{
    
}

bool Orc::Accept(Visitor *visitor)
{
    return visitor->Visit(*this);
}

// void Orc::SetAttackRange(std::size_t attackRange) noexcept
// {
//     this->_attackRange = attackRange;
// }

std::size_t Orc::GetMoveRange() const noexcept
{
    return this->_moveRange;
}

std::size_t Orc::GetAttackRange() const noexcept
{
    return this->_attackRange;
}

void Orc::SetAliveStatus(bool isAlive) noexcept
{
    this->_isAlive = isAlive;
}

bool Orc::GetAliveStatus() const noexcept
{
    return this->_isAlive;
}

std::size_t Orc::GetXCoordinate() const noexcept
{
    return this->_place.x;
}

std::size_t Orc::GetYCoordinate() const noexcept
{
    return this->_place.y;
}

std::string Orc::GetName() const noexcept
{
    return this->_name;
}

std::string Orc::GetDescription() const noexcept
{
    std::ostringstream oss;
    oss << "Orc " << this->_name << " " << this->_place.x << " " << this->_place.y;
    return oss.str(); 
}

Squirrel::Squirrel(const std::string &name, std::size_t coordX, std::size_t coordY):
    NPC(name, coordX, coordY, 5, 5)
{

}

bool Squirrel::Accept(Visitor *visitor)
{
    return visitor->Visit(*this);
}

// void Squirrel::SetAttackRange(std::size_t attackRange) noexcept
// {
//     this->_attackRange = attackRange;
// }

std::size_t Squirrel::GetMoveRange() const noexcept
{
    return this->_moveRange;
}

std::size_t Squirrel::GetAttackRange() const noexcept
{
    return this->_attackRange;
}

void Squirrel::SetAliveStatus(bool isAlive) noexcept
{
    this->_isAlive = isAlive;
}

bool Squirrel::GetAliveStatus() const noexcept
{
    return this->_isAlive;
}

std::size_t Squirrel::GetXCoordinate() const noexcept
{
    return this->_place.x;
}

std::size_t Squirrel::GetYCoordinate() const noexcept
{
    return this->_place.y;
}

std::string Squirrel::GetName() const noexcept
{
    return this->_name;
}

std::string Squirrel::GetDescription() const noexcept
{
    std::ostringstream oss;
    oss << "Squirrel " << this->_name << " " << this->_place.x << " " << this->_place.y;
    return oss.str(); 
}

Bear::Bear(const std::string &name, std::size_t coordX, std::size_t coordY):
    NPC(name, coordX, coordY, 5, 10)
{

}

bool Bear::Accept(Visitor *visitor)
{
    return visitor->Visit(*this);
}

// void Bear::SetAttackRange(std::size_t attackRange) noexcept
// {
//     this->_attackRange = attackRange;
// }

std::size_t Bear::GetMoveRange() const noexcept
{
    return this->_moveRange;
}

std::size_t Bear::GetAttackRange() const noexcept
{
    return this->_attackRange;
}

void Bear::SetAliveStatus(bool isAlive) noexcept
{
    this->_isAlive = isAlive;
}

bool Bear::GetAliveStatus() const noexcept
{
    return this->_isAlive;
}

std::size_t Bear::GetXCoordinate() const noexcept
{
    return this->_place.x;
}

std::size_t Bear::GetYCoordinate() const noexcept
{
    return this->_place.y;
}

std::string Bear::GetName() const noexcept
{
    return this->_name;
}

std::string Bear::GetDescription() const noexcept
{
    std::ostringstream oss;
    oss << "Bear " << this->_name << " " << this->_place.x << " " << this->_place.y;
    return oss.str(); 
}