#include "../include/factory.h"

Cell Factory::CreateNPC(const std::string &description)
{
    auto tokens = tokenize(description);
    if (tokens.size() != 4)
    {
        throw std::invalid_argument("invalid input");
    }

    Cell::Type type = Cell::Type::Empty;
    std::unique_ptr<NPC> object = nullptr;

    if (tokens[0] == "Orc")
    {
        type = Cell::Type::Orc;
        object = std::make_unique<Orc>(tokens[1], std::stoul(tokens[2]), std::stoul(tokens[3]));
    }
    else if (tokens[0] == "Squirrel")
    {
        type = Cell::Type::Squirrel;
        object = std::make_unique<Squirrel>(tokens[1], std::stoul(tokens[2]), std::stoul(tokens[3]));
    }
    else if (tokens[0] == "Bear")
    {
        type = Cell::Type::Bear;
        object = std::make_unique<Bear>(tokens[1], std::stoul(tokens[2]), std::stoul(tokens[3]));
    }
    else 
    {
        throw std::invalid_argument("invalid fighter type");
    }

    return Cell(type, std::move(object));
}

std::vector<std::string> Factory::tokenize(const std::string &description) noexcept
{
    std::vector<std::string> result;
    
    std::string current;
    for (const auto &symbol: description)
    {
        if (symbol == ' ')
        {
            if (!current.empty())
            {
                result.push_back(current);
                current.clear();
            }
            continue;
        }

        current += symbol;
    }
    
    if (!current.empty())
    {
        result.push_back(current);
        current.clear();
    }

    return result;
}