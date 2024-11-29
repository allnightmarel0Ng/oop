#include "common.h"

std::shared_ptr<Fighter> Fighter::_instance = nullptr;

Fighter::Fighter(std::shared_mutex &smutex, std::atomic<bool> &run):
    _smutex(smutex), _run(run)
{

}

void Fighter::ConstructInstance(std::shared_mutex &smutex, std::atomic<bool> &run)
{
    static auto newInstance = std::shared_ptr<Fighter>(new Fighter(smutex, run));
    _instance = newInstance;
}

std::shared_ptr<Fighter> Fighter::GetInstance()
{
    return _instance;
}

void Fighter::operator()() noexcept
{
    while (_run.load())
    {
        Cell *attacker = nullptr;
        Cell *defender = nullptr;

        {
            std::lock_guard<std::shared_mutex> sl(_smutex);
            if (_fights.empty())
            {
                continue;
            }

            attacker = &_fights.back().attacker;
            defender = &_fights.back().defender;
            _fights.pop();
        }
        
        if (attacker != nullptr && defender != nullptr && attacker->Object != nullptr && defender->Object != nullptr && attacker->Object->GetAliveStatus() && defender->Object->GetAliveStatus())
        {
            auto attackerPower = std::rand() % 6;
            auto defenderPower = std::rand() % 6;
            
            if (attackerPower > defenderPower)
            {
                defender->Object->SetAliveStatus(false);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

    }
}

void Fighter::addFight(Cell &attacker, Cell &defender)
{
    std::lock_guard<std::shared_mutex> lg(_smutex);
    _fights.push((Fight){attacker, defender});
}

void GameHandler::Game(std::size_t size)
{
    Field field(size, std::vector<Cell>(size, std::move(Cell())));

    std::vector<std::shared_ptr<Observer>> observers{
        std::make_unique<FileLogger>(), 
        std::make_unique<ConsoleLogger>()};


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
    std::mutex mutex;
    std::shared_mutex smutex;

    auto mover = std::make_shared<Mover>(field, observers);
    Fighter::ConstructInstance(smutex, run);
    std::thread fighting(std::ref(*Fighter::GetInstance()));
    std::thread movement([&field, &mover, &mutex, &smutex, &run]{
        while (run.load())
        {
            {
                std::lock_guard<std::mutex> lg(mutex);
                for (const auto &row: field)
                {
                    for (const auto &cell: row)
                    {
                        if (cell.Object != nullptr && cell.Object->GetAliveStatus())
                        {
                            cell.Object->Accept(mover.get());
                        }
                    }
                }
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });

    constexpr std::size_t seconds = 30;
    for (auto i = 0; i < seconds; ++i)
    {
        for (const auto &row: field)
        {
            for (const auto &cell: row)
            {
                if (cell.Object == nullptr || !cell.Object->GetAliveStatus() || cell.CellType == Cell::Type::Empty)
                {
                    std::cout << '.';
                    continue;
                }

                switch (cell.CellType)
                {
                case Cell::Type::Orc:
                    std::cout << 'O';
                    break;
                case Cell::Type::Bear:
                    std::cout << 'B';
                    break;
                case Cell::Type::Squirrel:
                    std::cout << 'S';
                    break;
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    for (const auto &row: field)
    {
        for (const auto &cell: row)
        {
            if (cell.Object == nullptr || !cell.Object->GetAliveStatus() || cell.CellType == Cell::Type::Empty)
            {
                continue;
            }

            std::cout << cell.Object->GetDescription() << std::endl;
        }
    }

    run.store(false);

    movement.join();
    fighting.join();
}