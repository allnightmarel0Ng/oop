#include "../include/observer.h"

#include "../include/npc.h"

std::string Observer::CellTypeToString(Cell::Type type) noexcept
{
    switch (type)
    {
    case Cell::Type::Orc:
        return "Orc";
    case Cell::Type::Squirrel:
        return "Squirrel";
    case Cell::Type::Bear:
        return "Bear";
    }
    return "Empty";
}

void FileLogger::HandleEvent(const Cell &killer, const Cell &victim) noexcept
{
    ofs << this->CellTypeToString(killer.CellType) << " " 
        << killer.Object->GetName() << " " 
        << killer.Object->GetXCoordinate() << " "
        << killer.Object->GetYCoordinate() << " "
        << "kills "
        << this->CellTypeToString(victim.CellType) 
        << victim.Object->GetName() << " " 
        << victim.Object->GetXCoordinate() << " "
        << victim.Object->GetYCoordinate() << std::endl;
}

void ConsoleLogger::HandleEvent(const Cell &killer, const Cell &victim) noexcept
{
    std::cout << this->CellTypeToString(killer.CellType) << " " 
              << killer.Object->GetName() << " " 
              << killer.Object->GetXCoordinate() << " "
              << killer.Object->GetYCoordinate() << " "
              << "kills "
              << this->CellTypeToString(victim.CellType) << " "
              << victim.Object->GetName() << " " 
              << victim.Object->GetXCoordinate() << " "
              << victim.Object->GetYCoordinate() << std::endl;
}