#include "../../include/mine_builder.h"
#include "../../include/miner.h"
#include "../include/test.hpp"
#include <iostream>

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
        test.ASSERT_EQ(room->condition() == Room::FREE);

        room = room->right();
        test.ASSERT_EQ(room->condition() == Room::GOLD);
        test.ASSERT_EQ(room->right()->condition() == Room::FENCE);
        test.ASSERT_EQ(room->up() == nullptr);
        test.ASSERT_EQ(room->pick_gold());

        room = room->down();
        test.ASSERT_EQ(room->right()->condition() == Room::FENCE);
        test.ASSERT_EQ(room->left()->condition() == Room::FENCE);
        test.ASSERT_EQ(room->up()->condition() == Room::FREE);
        test.ASSERT_EQ(room->down()->condition() == Room::GOLD);

        room = room->down();
        test.ASSERT_EQ(room->pick_gold());
        
        room = room->right();
        test.ASSERT_EQ(room->condition() == Room::GOLD);
        test.ASSERT_EQ(room->pick_gold());
        test.ASSERT_NOT(room->condition() == Room::GOLD);
        test.ASSERT_EQ(room->condition() == Room::FREE);

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
        DFS_LIMITED_SEARCH();
    }

private:
    Test test;

    void DFS_LIMITED_SEARCH()
    {
        // MineBuilder builder = MineBuilder("input/generated/teste.mine");
        MineBuilder builder = MineBuilder("input/generated/teste2.mine");
        // MineBuilder builder = MineBuilder("input/mine.txt");
        Mine mine = builder.build();

        Miner miner = Miner(mine.entrance(), mine.size());

        // auto [result, state, actions] = miner.dfs_limited(10000);
        // auto [result, state, actions] = miner.dfs_iterative(100);
        // auto [result, score, explored_states, actions] = miner.execute(Miner::DEEP_FIRST_SEARCH_LIMITED, 100);
        auto [result, score, explored_states, actions] = miner.execute(Miner::DEEP_FIRST_SEARCH_ITERATIVE, 100);

        State state;


        std::cout << "Result: " << result << std::endl;
        std::cout << "Remaining battery: " << miner.battery() << std::endl;
        std::cout << "Explored states: " << explored_states << std::endl;
        std::cout << "Picked gold: " << miner.gold() << std::endl;
        std::cout << "Score: " << score << std::endl;
        std::cout << "Actions Number: " << actions.size() << std::endl;
        std::cout << "Actions: " << state.actions_str(actions) << std::endl;


        
    }
};

int main()
{
    MinerTest().run();
}
