#ifndef __MINER_H__
#define __MINER_H__

#include <math.h>
#include <list>
#include <vector>
#include <string>
#include <map>
#include <deque>

#include "mine.h"
#include "room.h"
#include "node.h"
#include "state.h"
#include "result.h"
#include "problem.h"



class Miner
{
public:
    typedef std::tuple<bool, const State, std::list<State::Action>> Answer;
public:
    /* Inits the miner in the mine's entrance. */
    Miner(Room* position, unsigned int mine_size);

    /* Methods to guide the miner inside the mine. */
    const Room* left();
    const Room* right();
    const Room* up();
    const Room* down();

    const Room* position() const;

    /* Attribute getter's. */
    unsigned int battery() const;
    unsigned int gold() const;

    bool visited(const Room* room);

    bool goal_state(const State& state) const;

    unsigned int explored_rooms() const;

    std::string actions_str(std::list<State::Action> actions) const;

    Answer dfs_limited(const unsigned int curl, const unsigned int maxl);
    Answer dfs_iterative(const unsigned int iterations);

private:
    State dfs_limited(const unsigned int curl, const unsigned int maxl, State& state, std::list<State::Action>& actions, std::unordered_map<std::string, bool>& explored);
    Room* move(Room* next_room);

    /* Miner picks up the gold when possibile. */
    bool pick_gold();

    bool buy_battery();

    Node<State>* generate_states(Node<State>* state);

private:
    /* Personal attributes of the miner. */
    unsigned int _battery   = 0;
    unsigned int _gold      = 0;
    unsigned int _mine_size = 0;

    /* Current position inside the mine. */
    Room* _position = nullptr;

    unsigned int _explored_rooms = 0;

    Problem _problem;
};

#endif