#include <string>
#include <iostream>
#include <unistd.h>

#include "../include/time.h"
#include "../include/mine.h"
#include "../include/miner.h"
#include "../include/manhattan.h"
#include "../include/euclidian.h"
#include "../include/mine_builder.h"

void run(std::string path);
void limited_deep_first_search(MineBuilder builder);
void iterative_deep_first_search(MineBuilder builder);
void A_star(MineBuilder builder);
void limited_deep_first_search_with_heuristic(MineBuilder builder);
void print(std::string search_type, Miner::Result answer, double elapsed_time);

unsigned int maxl_dfs_limited = 0;
unsigned int maxi_dfs_iterative = 0;

int main()
{
    std::string path;
    std::string maxl;
    std::string maxi;

    std::cout << "Enter the path of the input file:" << std::endl;
    std::cin >> path;
    std::cout << std::endl;

    if (access(path.c_str(), F_OK) == -1)
    {
        std::cout << "File not found!" << std::endl;
        return -1;
    }

    std::cout << "Enter the maximum number of levels for limited depth searches: " << std::endl;
    std::cin >> maxl;
    std::cout << std::endl;

    std::cout << "Enter the maximum number of iterations for iterative depth searches: " << std::endl;
    std::cin >> maxi;
    std::cout << std::endl;

    maxl_dfs_limited = std::stoi(maxl);
    maxi_dfs_iterative = std::stoi(maxi); 

    run(path);  
}

void run(std::string path)
{
    MineBuilder builder = MineBuilder(path);

    limited_deep_first_search(builder);
    iterative_deep_first_search(builder);
    A_star(builder);
    limited_deep_first_search_with_heuristic(builder);
}

void limited_deep_first_search(MineBuilder builder)
{
    double t1 = time();

    Mine mine = builder.build();
    Miner miner = Miner(mine.entrance(), mine.size());
    Miner::Result result = miner.execute(Miner::DEEP_FIRST_SEARCH_LIMITED, maxl_dfs_limited);

    double t2 = time();

    print("Limited Deep First Search (max " + std::to_string(maxl_dfs_limited) + " levels)", result, elapsed(t1, t2));
}

void iterative_deep_first_search(MineBuilder builder)
{
    double t1 = time();

    Mine mine = builder.build();
    Miner miner = Miner(mine.entrance(), mine.size());
    Miner::Result result = miner.execute(Miner::DEEP_FIRST_SEARCH_ITERATIVE, maxi_dfs_iterative);

    double t2 = time();

    print("Iterative Deep First Search (max " + std::to_string(maxi_dfs_iterative) + " iterations)", result, elapsed(t1, t2));
}

void A_star(MineBuilder builder)
{
    double t1 = time();

    Mine mine = builder.build();

    Heuristic* manhattan = new ManhattanDistance(mine);
    Miner miner = Miner(mine.entrance(), mine.size(), manhattan);

    Miner::Result result = miner.execute(Miner::A_STAR);

    double t2 = time();

    delete manhattan;

    print("A*", result, elapsed(t1, t2));
}

void limited_deep_first_search_with_heuristic(MineBuilder builder)
{
    double t1 = time();

    Mine mine = builder.build();

    Heuristic* euclidian = new EuclidianDistance(mine);
    Miner miner = Miner(mine.entrance(), mine.size(), euclidian);

    Miner::Result result = miner.execute(Miner::DEEP_FIRST_SEARCH_ITERATIVE, maxl_dfs_limited);

    double t2 = time();
    delete euclidian;

    print("Iterative Deep First Search with Heuristic (max " + std::to_string(maxi_dfs_iterative) + " iterations)", result, elapsed(t1, t2));
}

void print(std::string search_type, Miner::Result answer, double elapsed_time)
{
    auto [result, score, explored_states, actions] = answer;

    std::cout << "***** " << search_type << " *****" << std::endl;
    std::cout << "Result: " << (result ? "Success" : "Failed") << std::endl;
    std::cout << "Score: " << score << std::endl;
    std::cout << "Explored States: " << explored_states << std::endl;
    std::cout << "Actions: " << State().actions_str(actions) << std::endl;
    std::cout << "Elapsed Time: " << elapsed_time << " ms" << std::endl;
    std::cout << std::endl;
}