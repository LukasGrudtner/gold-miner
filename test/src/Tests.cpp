#include "../../include/mine_builder.h"
#include "../../include/miner.h"
#include "../include/test.hpp"
#include <iostream>

class RoomTest
{
public:
    void run()
    {
        EQUALS();
    }

private:
    Test test;

    void EQUALS()
    {
        Room r1 = Room(Room::FREEWAY);
        Room r2 = Room(Room::FENCE);
        Room r3 = Room(Room::GOLD);
        Room r4 = Room(Room::FREEWAY);
        Room r5 = Room(Room::GOLD);
        Room r6 = Room(Room::FREEWAY);

        r1.set_right(&r2);
        r1.set_left(&r3);

        r4.set_right(&r2);
        r4.set_left(&r3);

        test.ASSERT_EQ(r1 == r4);

        r4.set_down(&r1);
        test.ASSERT_NOT(r1 == r4);
        test.ASSERT_EQ(r3 == r5);

        r5.pick_gold();
        test.ASSERT_EQ(r5 == r6);
        test.ASSERT_NOT(r3 == r5);

        test.evaluate("ROOM :: equals()");
    }
};

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
        // MINING();
        // EXPLORED();
        DFS_LIMITED_SEARCH();
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

    void EXPLORED()
    {
        MineBuilder builder = MineBuilder("input/generated/teste.mine");
        Mine mine = builder.build();

        Miner miner = Miner(mine.entrance(), mine.size());

        Result result;
        // result._explored.insert(mine.entrance(), mine.entrance());
        // result._explored.insert(std::pair<const Room*, const Room*>(mine.entrance(), mine.entrance()));
        result._explored[mine.entrance()] = mine.entrance();
        // const Room* r1 = result._explored.at(mine.entrance());
        auto t = result._explored[mine.entrance()];
        if (t)
            std::cout << "teste" << std::endl;

        auto it = result._explored.find(mine.entrance());
        std::cout << (it == result._explored.end()) << std::endl;
        // result._explored.insert(mine.entrance(), mine.entrance());
        // const Room* r2 = result._explored.at(mine.entrance());
    }

    void DFS_LIMITED_SEARCH()
    {
        // MineBuilder builder = MineBuilder("input/generated/teste.mine");
        MineBuilder builder = MineBuilder("input/mine.txt");
        Mine mine = builder.build();

        Miner miner = Miner(mine.entrance(), mine.size());

        auto [result, state, actions] = miner.dfs_limited(0, 10000);
        // auto [result, state, actions] = miner.dfs_iterative(100);

        std::cout << result << std::endl;

        std::cout << "Result: " << result << std::endl;
        std::cout << "Initial battery: " << miner.battery() << std::endl;
        std::cout << "Remaining battery: " << state.battery() << std::endl;
        std::cout << "Explored states: " << miner.explored_rooms() << std::endl;
        std::cout << "Picked gold: " << state.gold() << std::endl;
        std::cout << "Actions Number: " << actions.size() << std::endl;
        std::cout << "Actions: " << miner.actions_str(actions) << std::endl;


        
    }
};

int main()
{
    // RoomTest().run();
    // MineBuilderTest().run();
    MinerTest().run();
}
