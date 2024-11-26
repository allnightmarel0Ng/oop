#include "common.h"

Fighter::Fighter(std::vector<std::vector<Cell>> &field, const std::vector<std::shared_ptr<Observer>> &observers, std::mutex &fieldMutex):
    _field(field), _observers(observers), _fights(), _mutex(fieldMutex)
{

}

bool Fighter::Visit(Orc &ref) noexcept
{
    auto x = ref.GetXCoordinate();
    auto y = ref.GetYCoordinate();
    
    move(&ref, x, y);


    

    return true;
    // int attackRange = ref.GetAttackRange();

    // auto leftBound = std::max(x - attackRange, 0);
    // auto rightBound = std::min(x + attackRange, 500);

    // auto upperBound = std::max(y - attackRange, 0);
    // auto lowerBound = std::min(y + attackRange, 500);

    // for (std::size_t i = leftBound; i <= rightBound; i++)
    // {
    //     for (std::size_t j = upperBound; j <= lowerBound; j++)
    //     {
    //         if (i == x || j == y)
    //         {
    //             continue;
    //         }

    //         auto &current = _field[i][j];
    //         if (current.CellType == Cell::Type::Empty || current.CellType == Cell::Type::Squirrel)
    //         {
    //             continue;
    //         }

    //         notify(_field[x][y], current);
    //         current.Object->SetAliveStatus(false);
    //         // current.Object = nullptr;
    //     }
    // }
}

bool Fighter::Visit(Squirrel &ref) noexcept
{
    return false;
}

bool Fighter::Visit(Bear &ref) noexcept
{
    int x = ref.GetXCoordinate();
    int y = ref.GetYCoordinate();
    return true;
    // int attackRange = ref.GetAttackRange();

    // auto leftBound = std::max(x - attackRange, 0);
    // auto rightBound = std::min(x + attackRange, 500);

    // auto upperBound = std::max(y - attackRange, 0);
    // auto lowerBound = std::min(y + attackRange, 500);

    // for (std::size_t i = leftBound; i <= rightBound; i++)
    // {
    //     for (std::size_t j = upperBound; j <= lowerBound; j++)
    //     {
    //         if (i == x || j == y)
    //         {
    //             continue;
    //         }

    //         auto &current = _field[i][j];
    //         if (current.CellType == Cell::Type::Squirrel)
    //         {
    //             notify(_field[x][y], current);
    //             current.Object->SetAliveStatus(false);
    //             // current.Object = nullptr;
    //         }
    //     }
    // }
}

void Fighter::operator()()
{
    
}

void Fighter::move(NPC *ptr, std::size_t &x, std::size_t &y)
{
    auto moveRange = ptr->GetMoveRange();

    std::uint8_t direction = std::rand() % 4;
    auto newX = x;
    auto newY = y;

    if (direction == 0)
    {
        newX = std::max<std::size_t>(0, x - moveRange);
    }
    else if (direction == 1)
    {
        newX = std::min<std::size_t>(_field.size(), x + moveRange);
    }
    else if (direction == 2)
    {
        newY = std::max<std::size_t>(0, y - moveRange);
    }
    else if (direction == 3)
    {
        newY = std::min<std::size_t>(_field.size(), y + moveRange);
    }

    if (_field[newX][newY].Object == nullptr || !_field[newX][newY].Object->GetAliveStatus())
    {
        _field[newX][newY] = std::move(_field[x][y]);
        _field[x][y] = Cell();
        x = newX;
        y = newY;
    }
}

void Fighter::notify(const Cell &killer, const Cell &victim) const noexcept
{
    for (const auto &ptr: _observers)
    {
        ptr->HandleEvent(killer, victim);
    }
}