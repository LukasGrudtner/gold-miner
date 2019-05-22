/**
 * Author: Lukas Derner Grüdtner
 **/

#ifndef __MINER_H__
#define __MINER_H__

#include <set>
#include <list>
#include <math.h>
#include <string>
#include <unordered_map>

#include "mine.h"
#include "room.h"
#include "state.h"
#include "problem.h"

/* Definition of the agent to this problem. */
class Miner
{
public:
    /* Type definition of an Answer (result, goal state, action list). */
    typedef std::tuple<bool, const State, std::list<State::Action>> Answer;

    /* Type definition of search strategies. */
    typedef unsigned char SearchStrategy;
    static const SearchStrategy DEEP_FIRST_SEARCH_LIMITED   = (1 << 0);
    static const SearchStrategy DEEP_FIRST_SEARCH_ITERATIVE = (1 << 1);
    static const SearchStrategy A_STAR                      = (1 << 2);

    /* Type definition of a Result (result, score, explored rooms, action list); */
    typedef std::tuple<bool, unsigned int, unsigned int, std::list<State::Action>> Result;

public:
    /* Inits the miner in the mine's entrance. */
    Miner(Room* position, unsigned int mine_size);

    /* Insert an heuristic to guide the miner. */
    Miner(Room* position, unsigned int mine_size, Heuristic* heuristic);

    /* Attribute getter's. */
    const Room*     position()  const;
    unsigned int    battery()   const;
    unsigned int    gold()      const;

    /* Checks if the given state is a goal state, according the problem. */
    bool is_goal_state(const State& state) const;

    /* Return the number of rooms already explored. */
    unsigned int number_explored_rooms() const;

    /* The miner will search a way to a goal state and will follow it. */
    Result execute(SearchStrategy strategy, unsigned int parameter=1);

private:
    /* Methods to guide the miner inside the mine. */
    const Room* left();
    const Room* right();
    const Room* up();
    const Room* down();

    /* Move to the next room. */
    Room* move(Room* next_room);

    /* Miner picks up the gold when possibile. */
    bool pick_gold();

    /* Buy more batteries with the picked gold. */
    bool buy_battery();
    
    /* Search for the action list to move inside the mine. */
    Answer search(SearchStrategy strategy, unsigned int parameter);

    /* Explore the mine according the action list. */
    void explore(std::list<State::Action> actions);

    /* Give the score according the remaining battery, picked gold, states visited and actions number. */
    int score() const;

    /* Limited deep first search function. */
    Answer  dfs_limited(const unsigned int maxl);
    State   dfs_limited(const unsigned int curl, const unsigned int maxl, State& state, std::list<State::Action>& actions, std::unordered_map<std::string, bool>& explored);

    /* Iterative deep first search function. */
    Answer dfs_iterative(const unsigned int iterations);

    /* A* algorithm. */
    Answer A_star();

    /* Support function to reconstruct the path searched in the A* algorithm. */
    std::list<State::Action> reconstruct_path(std::map<std::string, State> came_from, State position);

private:
    /* Personal attributes of the miner. */
    unsigned int _battery   = 0;
    unsigned int _gold      = 0;
    unsigned int _mine_size = 0;

    /* Current position inside the mine. */
    Room* _position = nullptr;

    /* Number of explored rooms. */
    unsigned int _explored_rooms = 0;

    /* Number of actions. */
    unsigned int _actions_count = 0;

    /* Instance of the problem (search for gold inside the mine). */
    Problem _problem;
};

#endif