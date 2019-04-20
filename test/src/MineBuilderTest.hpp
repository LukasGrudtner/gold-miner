#ifndef __MINE_BUILDER_TEST_CPP__
#define __MINE_BUILDER_TEST_CPP__

#include "../../include/mine_builder.h"
#include "../include/test.hpp"

Test test;

class MineBuilderTest
{
    
public:
    static void BUILDER()
    {
        MineBuilder builder = MineBuilder("input/mine.txt");
        Mine mine = builder.build();

        const Room* room = mine.entrance();
        test.ASSERT_EQ(room->goal() == Room::FREEWAY);

        test.evaluate("MINE_BUILDER :: entrance()");
    }

    void run()
    {
        BUILDER();
    }

};



#endif