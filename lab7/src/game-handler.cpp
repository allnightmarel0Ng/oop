#include "common.h"

void GameHandler::Game(std::size_t size)
{
    Field field(size, std::vector<Cell>(size, std::move(Cell())));

    std::vector<std::shared_ptr<Observer>> observers{
        std::make_unique<FileLogger>(), 
        std::make_unique<ConsoleLogger>()};

    std::unique_ptr<Visitor> visitor = std::make_unique<Fighter>(field, observers);

    for (std::size_t i = 0; i < 50; ++i)
    {
        std::size_t coordX = 0;
        std::size_t coordY = 0;
        
        do
        {
            coordX = std::rand() % size;
            coordY = std::rand() % size;
        } 
        while (field[coordX][coordY].Object != nullptr);

        auto type = static_cast<Cell::Type>(std::rand() % 3);

        std::ostringstream descriptionBuilder;
        descriptionBuilder << [type]
        {
            if (type == Cell::Type::Orc)
            {
                return "Orc ";
            }
            else if (type == Cell::Type::Squirrel)
            {
                return "Squirrel ";
            }
            return "Bear ";
        }();
        descriptionBuilder << i << " " << coordX << " " << coordY;

        field[coordX][coordY] = Factory::CreateNPC(descriptionBuilder.str());
    }

    std::atomic<bool> run = true;
    std::mutex fieldMutex;

    std::thread movement([&field, &visitor, &fieldMutex, &run]{
        while (run.load())
        {
            {
                std::shared_lock<std::mutex> sl(fieldMutex);
                for (const auto &row: field)
                {
                    for (const auto &cell: row)
                    {
                        if (cell.Object != nullptr && cell.Object->GetAliveStatus())
                        {
                            std::lock_guard<std::mutex> lg(fieldMutex);
                            cell.Object->Accept(visitor.get());
                        }
                    }
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    });

    movement.join();
}