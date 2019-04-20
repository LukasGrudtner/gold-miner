#include "../../include/mine_builder.h"
#include "../include/test.hpp"

Test test;

class MineBuilderTest
{
    
public:
    void BUILDER()
    {
        MineBuilder builder = MineBuilder("input/mine.txt");
        Mine mine = builder.build();

        const Room* room = mine.entrance();
        test.ASSERT_EQ(room->goal() == Room::FREEWAY);

        room = room->right();
        test.ASSERT_EQ(room->goal() == Room::FREEWAY);

        test.evaluate("MINE_BUILDER :: entrance()");
    }

    void run()
    {
        BUILDER();
    }
};

int main()
{
    MineBuilderTest mineBuilder;
    mineBuilder.run();
}
