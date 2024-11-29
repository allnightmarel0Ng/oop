#include "../include/fighter.h"

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