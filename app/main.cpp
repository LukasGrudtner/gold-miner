#include <string>
#include <iostream>
#include <unistd.h>

#include "../include/mine.h"
#include "../include/miner.h"
#include "../include/mine_builder.h"

#define DEFAULT_PATH "input/generated/teste2.mine"

void run(std::string path);
void limited_deep_first_search(MineBuilder builder);
void iterative_deep_first_search(MineBuilder builder);
void print(std::string search_type, Miner::Result answer);

unsigned int maxl_dfs_limited = 0;
unsigned int maxi_dfs_iterative = 0;

int main()
{
    std::string path;
    std::string maxl;
    std::string maxi;

    std::cout << "Insira o path do arquivo de entrada relativo à raiz do projeto (test para o default): " << std::endl;
    std::cin >> path;
    std::cout << std::endl;

    if (access(path.c_str(), F_OK) == -1)
    {
        std::cout << "Arquivo não existente!" << std::endl;
        return -1;
    }

    std::cout << "Insira o número máximo de níveis para a busca em profundidade limitada: " << std::endl;
    std::cin >> maxl;
    std::cout << std::endl;

    std::cout << "Insira o número máximo de iterações para a busca em profundidade iterativa: " << std::endl;
    std::cin >> maxi;
    std::cout << std::endl;

    maxl_dfs_limited = std::stoi(maxl);
    maxi_dfs_iterative = std::stoi(maxi); 

    run(path);  
}

void run(std::string path)
{
    if (path == "test")
        path = DEFAULT_PATH;

    MineBuilder builder = MineBuilder(path);
    Mine mine = builder.build();

    limited_deep_first_search(builder);
    iterative_deep_first_search(builder);
}

void limited_deep_first_search(MineBuilder builder)
{
    Mine mine = builder.build();
    Miner miner = Miner(mine.entrance(), mine.size());
    Miner::Result result = miner.execute(Miner::DEEP_FIRST_SEARCH_LIMITED, maxl_dfs_limited);

    print("Limited Deep First Search (max " + std::to_string(maxl_dfs_limited) + " levels)", result);
}

void iterative_deep_first_search(MineBuilder builder)
{
    Mine mine = builder.build();
    Miner miner = Miner(mine.entrance(), mine.size());
    Miner::Result result = miner.execute(Miner::DEEP_FIRST_SEARCH_ITERATIVE, maxi_dfs_iterative);

    print("Iterative Deep First Search (max " + std::to_string(maxi_dfs_iterative) + " iterations)", result);
}

void print(std::string search_type, Miner::Result answer)
{
    auto [result, score, explored_states, actions] = answer;

    std::cout << "***** " << search_type << " *****" << std::endl;
    std::cout << "Result: " << (result ? "Success" : "Failed") << std::endl;
    std::cout << "Score: " << score << std::endl;
    std::cout << "Explored States: " << explored_states << std::endl;
    std::cout << "Actions: " << State().actions_str(actions) << std::endl;
    std::cout << std::endl;
}