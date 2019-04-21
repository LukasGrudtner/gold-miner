#include "../../include/mine_builder.h"
#include "../../include/miner.h"
#include "../include/test.hpp"

class MineBuilderTest
{
public:
    void run()
    {
        WANDERER();
    }

private:
    Test test;

    /*  Going through the mine. */
    void WANDERER()
    {
        MineBuilder builder = MineBuilder("input/mine.txt");
        Mine mine = builder.build();

        Room* room = mine.entrance();
        test.ASSERT_EQ(room->goal() == Room::FREEWAY);

        room = room->right();
        test.ASSERT_EQ(room->goal() == Room::GOLD);
        test.ASSERT_EQ(room->right()->goal() == Room::FENCE);
        test.ASSERT_EQ(room->up() == nullptr);
        test.ASSERT_EQ(room->pick_gold());

        room = room->down();
        test.ASSERT_EQ(room->right()->goal() == Room::FENCE);
        test.ASSERT_EQ(room->left()->goal() == Room::FENCE);
        test.ASSERT_EQ(room->up()->goal() == Room::FREEWAY);
        test.ASSERT_EQ(room->down()->goal() == Room::GOLD);

        room = room->down();
        test.ASSERT_EQ(room->pick_gold());
        
        room = room->right();
        test.ASSERT_EQ(room->goal() == Room::GOLD);
        test.ASSERT_EQ(room->pick_gold());
        test.ASSERT_NOT(room->goal() == Room::GOLD);
        test.ASSERT_EQ(room->goal() == Room::FREEWAY);

        room = room->down();
        test.ASSERT_NOT(room->pick_gold());

        room = room->down();
        test.ASSERT_EQ(room == nullptr);

        test.evaluate("MINE_BUILDER :: wanderer()");
    }
};

class MinerTest
{
public:
    void run()
    {
        MINING();
    }

private:
    Test test;

    void MINING()
    {
        MineBuilder builder = MineBuilder("input/mine.txt");
        Mine mine = builder.build();

        Miner miner = Miner(mine.entrance(), mine.size());

        test.ASSERT_EQ(miner.battery() == 8);
        test.ASSERT_EQ(miner.gold() == 0);

        test.ASSERT_NOT(miner.up());    /* doesn't exist */
        test.ASSERT_NOT(miner.left());  /* doesn't exist */
        test.ASSERT_NOT(miner.down());  /* fence */
        test.ASSERT_EQ(miner.right());  /* freeway */

        test.ASSERT_EQ(miner.battery() == 7); /* size**(1.5) - 1 */
        test.ASSERT_EQ(miner.gold() == 1);

        test.ASSERT_EQ(miner.left());
        test.ASSERT_EQ(miner.right());
        test.ASSERT_EQ(miner.battery() == 5);
        test.ASSERT_EQ(miner.gold() == 1);

        miner.down();
        miner.down();
        miner.right();
        test.ASSERT_EQ(miner.gold() == 3);
        test.ASSERT_EQ(miner.battery() == 2);

        miner.down();
        miner.up();
        test.ASSERT_EQ(miner.battery() == 0);
        test.ASSERT_EQ(miner.down());
        test.ASSERT_EQ(miner.gold() == 2);
        test.ASSERT_EQ(miner.battery() == 39); /* size**(1.5) * 5 - 1 */

        test.evaluate("MINER :: mining()");
    }
};

int main()
{
    MineBuilderTest().run();
    MinerTest().run();
}
