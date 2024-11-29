#include <gtest/gtest.h>

#include <game_handler.h>

TEST(game, test1)
{
    std::string input =
        "2 load ../tests/in.txt\n"
        "4 50\n"
        "3\n"
        "5\n";
    
    std::istringstream iss(input);
    std::ostringstream oss;

    GameHandler::Game(iss, oss);

    ASSERT_EQ(oss.str(), "Squirrel Speedy 30 80\n"
                        "Squirrel Whiskers 40 70\n"
                        "Squirrel Twitchy 50 150\n"
                        "Squirrel Scamper 60 90\n"
                        "Squirrel Fluffy 70 100\n"
                        "Squirrel Chitter 90 120\n"
                        "Bear Grizzly 200 400\n"
                        "Bear Brown 270 330\n"
                        "Bear Panda 300 380\n"
                        "Bear Polar 350 450\n"
                        "Squirrel Nutty 450 300\n");
}

TEST(game, test2)
{
    std::string input = 
        "2 load ../tests/in.txt\n"
        "4 200\n"
        "3\n"
        "1 Bear Name 200 200\n"
        "4 100\n"
        "3\n"
        "5\n";
    
    std::istringstream iss(input);
    std::ostringstream oss;

    GameHandler::Game(iss, oss);

    ASSERT_EQ(oss.str(), "Bear Polar 350 450\n"
                        "Bear Name 200 200\n"
                        "Bear Polar 350 450\n");
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}