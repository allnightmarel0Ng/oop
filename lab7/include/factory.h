#ifndef LAB7_FACTORY_H
#define LAB7_FACTORY_H

#include <stdexcept>

#include "npc.h"

class Factory
{

public:
    Factory() = delete;

public:
    static Cell CreateNPC(const std::string &description);

private:
    static std::vector<std::string> tokenize(const std::string &description) noexcept;

};

#endif