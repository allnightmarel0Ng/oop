#include "../include/visitor.h"

#include "../include/npc.h"

Fighter::Fighter(std::vector<std::vector<Cell>> &field, const std::vector<std::shared_ptr<Observer>> &observers):
    _field(field), _observers(observers)
{

}

void Fighter::Visit(Orc &ref) noexcept
{
    int x = ref.GetXCoordinate();
    int y = ref.GetYCoordinate();
    int attackRange = ref.GetAttackRange();

    auto leftBound = x < attackRange ? 0 : x - attackRange;
    auto rightBound = std::min(x + attackRange, 499);

    auto upperBound = y < attackRange ? 0 : y - attackRange;
    auto lowerBound = std::min(y + attackRange, 499);

    for (std::size_t i = leftBound; i <= rightBound; i++)
    {
        for (std::size_t j = upperBound; j <= lowerBound; j++)
        {
            if (i == x || j == y)
            {
                continue;
            }

            auto &current = _field[i][j];
            if (current.CellType == Cell::Type::Empty || current.CellType == Cell::Type::Squirrel)
            {
                continue;
            }

            notify(_field[x][y], current);
            current.Object->SetAliveStatus(false);
            // current.Object = nullptr;
        }
    }
}

void Fighter::Visit(Squirrel &ref) noexcept
{
    
}

void Fighter::Visit(Bear &ref) noexcept
{
    int x = ref.GetXCoordinate();
    int y = ref.GetYCoordinate();
    int attackRange = ref.GetAttackRange();

    auto leftBound = x < attackRange ? 0 : x - attackRange;
    auto rightBound = std::min(x + attackRange, 499);

    auto upperBound = y < attackRange ? 0 : y - attackRange;
    auto lowerBound = std::min(y + attackRange, 499);

    for (std::size_t i = leftBound; i <= rightBound; i++)
    {
        for (std::size_t j = upperBound; j <= lowerBound; j++)
        {
            if (i == x || j == y)
            {
                continue;
            }

            auto &current = _field[i][j];
            if (current.CellType == Cell::Type::Squirrel)
            {
                notify(_field[x][y], current);
                current.Object->SetAliveStatus(false);
                // current.Object = nullptr;
            }
        }
    }
}

void Fighter::notify(const Cell &killer, const Cell &victim) const noexcept
{
    for (const auto &ptr: _observers)
    {
        ptr->HandleEvent(killer, victim);
    }
}