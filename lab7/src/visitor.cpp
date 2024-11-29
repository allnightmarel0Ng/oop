#include "common.h"

Mover::Mover(std::vector<std::vector<Cell>> &field, const std::vector<std::shared_ptr<Observer>> &observers):
    _field(field), _observers(observers)
{

}

void Mover::Visit(Orc &ref) noexcept
{
    auto &x = ref.GetXCoordinate();
    auto &y = ref.GetYCoordinate();

    move(&ref, x, y);

    auto attackRange = ref.GetAttackRange();

    auto leftBorder = x < attackRange ? 0 : x - attackRange;
    auto rightBorder = std::min<std::size_t>(x + attackRange, _field.size() - 1);
    auto upperBorder = y < attackRange ? 0 : y - attackRange;
    auto lowerBorder = std::min<std::size_t>(y + attackRange, _field.size() - 1);

    for (auto i = leftBorder; i < rightBorder; ++i)
    {
        for (auto j = upperBorder; j < lowerBorder; ++j)
        {
            if (i == x && j == y)
            {
                continue;
            }
            
            auto &current = _field[i][j];
            if (current.Object == nullptr || !current.Object->GetAliveStatus() || current.CellType == Cell::Type::Squirrel || current.CellType == Cell::Type::Empty)
            {
                continue;
            }

            Fighter::GetInstance()->addFight(_field[x][y], current);
        }
    }
}

void Mover::Visit(Squirrel &ref) noexcept
{    
    move(&ref, ref.GetXCoordinate(), ref.GetYCoordinate());
}

void Mover::Visit(Bear &ref) noexcept
{    
    auto &x = ref.GetXCoordinate();
    auto &y = ref.GetYCoordinate();
    move(&ref, x, y);

    int attackRange = ref.GetAttackRange();

    auto leftBound = x < attackRange ? 0 : x - attackRange; // std::max<std::size_t>(x - attackRange, 0);
    auto rightBound = std::min<std::size_t>(x + attackRange, _field.size() - 1);

    auto upperBound = y < attackRange ? 0 : y - attackRange; // std::max<std::size_t>(y - attackRange, 0);
    auto lowerBound = std::min<std::size_t>(y + attackRange, _field.size() - 1);

    for (std::size_t i = leftBound; i <= rightBound; i++)
    {
        for (std::size_t j = upperBound; j <= lowerBound; j++)
        {
            if (i == x && j == y)
            {
                continue;
            }

            auto &current = _field[i][j];
            if (current.CellType == Cell::Type::Squirrel)
            {
                Fighter::GetInstance()->addFight(_field[x][y], current);
            }
        }
    }
}

void Mover::move(NPC *ptr, std::size_t &x, std::size_t &y)
{
    auto moveRange = ptr->GetMoveRange();

    std::uint8_t direction = std::rand() % 4;
    auto newX = x;
    auto newY = y;

    if (direction == 0)
    {
        newX = x < moveRange ? 0 : x - moveRange;
    }
    else if (direction == 1)
    {
        newX = std::min(_field.size() - 1, x + moveRange);
    }
    else if (direction == 2)
    {
        newY = y < moveRange ? 0 : y - moveRange;
    }
    else if (direction == 3)
    {
        newY = std::min(_field.size() - 1, y + moveRange);
    }

    if (_field[newX][newY].Object == nullptr || !_field[newX][newY].Object->GetAliveStatus())
    {
        _field[newX][newY].CellType = _field[x][y].CellType;
        _field[newX][newY].Object = std::move(_field[x][y].Object);
        _field[x][y] = Cell();
        x = newX;
        y = newY;
    }
}

void Mover::notify(const Cell &killer, const Cell &victim) const noexcept
{
    for (const auto &ptr: _observers)
    {
        ptr->HandleEvent(killer, victim);
    }
}