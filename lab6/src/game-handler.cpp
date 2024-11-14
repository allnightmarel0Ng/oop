#include "common.h"

void GameHandler::Game(std::istream &is, std::ostream &os)
{
    std::vector<std::vector<Cell>> field(501, std::vector<Cell>(501, std::move(Cell())));

    std::vector<std::shared_ptr<Observer>> observers{
        std::make_unique<FileLogger>(), 
        std::make_unique<ConsoleLogger>()};

    std::unique_ptr<Visitor> visitor = std::make_unique<Fighter>(field, observers);

    GameHandler::PrintMenu();
    bool run = true;
    while (run)
    {
        std::cout << ">> ";
        int command = 0;
        is >> command;

        std::string subcommand;
        std::string filepath;
        std::size_t attackRange = 0;

        switch (command)
        {
        case 1:
            GameHandler::HandleAddNPC(is, field);
            break;
        case 2:
            is >> subcommand;
            is >> filepath;

            if (subcommand == "load")
            {
                GameHandler::HandleLoadFile(filepath, field);
            }
            else if (subcommand == "save")
            {
                GameHandler::HandleSaveFile(filepath, field);
            }
            else
            {
                os << "wrong command" << std::endl;
            }
            break;
        case 3:
            GameHandler::PrintObjects(os, field);
            break;
        case 4:
            is >> attackRange;
            GameHandler::HandleFight(visitor, field, attackRange);
            break;
        case 5:
            run = false;
            break;
        case 6:
            GameHandler::PrintMenu();
            break;
        }
    }
}

void GameHandler::HandleAddNPC(std::istream &is, std::vector<std::vector<Cell>> &field)
{
    std::string description;
    std::getline(is, description);
    try 
    {
        auto newNPC = Factory::CreateNPC(description);
        field[newNPC.Object->GetXCoordinate()][newNPC.Object->GetYCoordinate()] = std::move(newNPC);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}

void GameHandler::HandleLoadFile(const std::string &filepath, std::vector<std::vector<Cell>> &field)
{
    std::ifstream ifs;
    ifs.open(filepath);
    if (!ifs.is_open())
    {
        std::cout << "invalid filepath: " << filepath << std::endl;
        return;
    }

    while (!ifs.eof())
    {
        HandleAddNPC(ifs, field);
    }
}

void GameHandler::PrintObjects(std::ostream &os, const std::vector<std::vector<Cell>> &field) noexcept
{
    for (std::size_t i = 0; i < field.size(); i++)
    {
        for (std::size_t j = 0; j < field[i].size(); j++)
        {
            if (field[i][j].Object != nullptr && field[i][j].Object->GetAliveStatus())
            {
                os << field[i][j].Object->GetDescription() << std::endl;
            }
        }
    }
}

void GameHandler::HandleSaveFile(const std::string &filepath, const std::vector<std::vector<Cell>> &field) noexcept
{
    std::ofstream ofs;
    ofs.open(filepath);
    if (!ofs.is_open())
    {
        std::cout << "invalid filepath: " << filepath << std::endl;
        return;
    }

    PrintObjects(ofs, field);
}

void GameHandler::HandleFight(const std::unique_ptr<Visitor> &visitor, std::vector<std::vector<Cell>> &field, std::size_t attackRange) noexcept
{
    for (std::size_t i = 0; i < field.size(); i++)
    {
        for (std::size_t j = 0; j < field[i].size(); j++)
        {
            if (field[i][j].Object != nullptr && field[i][j].CellType != Cell::Type::Empty)
            {
                field[i][j].Object->SetAttackRange(attackRange);
                field[i][j].Object->Accept(visitor.get());
            }
        }
    }

    for (std::size_t i = 0; i < field.size(); i++)
    {
        for (std::size_t j = 0; j < field[i].size(); j++)
        {
            if (field[i][j].Object != nullptr && !field[i][j].Object->GetAliveStatus())
            {
                field[i][j].CellType = Cell::Type::Empty;
            }
        }
    }   
}

void GameHandler::PrintMenu() noexcept
{
    std::cout << "1 - add NPC." << std::endl;
    std::cout << "\tUsage: 1 input following data: Type Name X Y, where Type = Orc | Squirrel | Bear" << std::endl;
    
    std::cout << "2 - load/save from/to file." << std::endl;
    std::cout << "\tUsage: 2 load/save filepath. Data format in filepath should look like in the first command" << std::endl;
    
    std::cout << "3 - print object list to console." << std::endl;

    std::cout << "4 - start fight mode." << std::endl;
    std::cout << "\tUsage: 4 <value>. Value represents attack range of units" << std::endl;

    std::cout << "5 - exit." << std::endl;

    std::cout << "6 - print this menu." << std::endl;
}