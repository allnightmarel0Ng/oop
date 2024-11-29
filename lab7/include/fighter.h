#ifndef LAB7_FIGHTER_H
#define LAB7_FIGHTER_H

#include <atomic>
#include <thread>
#include <shared_mutex>
#include <queue>

#include "npc.h"

class Fighter
{

private:
    explicit Fighter(std::shared_mutex &smutex, std::atomic<bool> &run);

public:    
    Fighter(Fighter &&other) = delete;

public:
    static void ConstructInstance(std::shared_mutex &smutex, std::atomic<bool> &run);
    static std::shared_ptr<Fighter> GetInstance();

public:
    void operator()() noexcept;
    void addFight(Cell &attacker, Cell &defender);

private:
    struct Fight 
    {
        Cell &attacker, &defender;
    };

    std::queue<Fight> _fights;
    std::shared_mutex &_smutex; 
    std::atomic<bool> &_run;

    static std::shared_ptr<Fighter> _instance;
};

#endif