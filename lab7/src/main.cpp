#include <game_handler.h>

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    GameHandler::Game(100);
    return 0;
}