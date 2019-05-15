#ifndef __PROBLEM_H__
#define __PROBLEM_H__

#include <list>
#include <vector>
#include "state.h"
#include <algorithm>
#include <tuple>
#include <math.h>
#include <stack>
#include <deque>

#define BATTERY_POWER 1.5

class Problem
{
public:
    Problem();
    Problem(unsigned int problem_size, State initial_state);

    /* Return a list of successors states for a given state. */
    std::list<const State> successors(State& state);

    /* Checks if the given state is a target. */
    bool goal(const State& state) const;

    /* Return the path cost of the problem. */
    unsigned int path_cost() const;

    /* Returns the initial state. */
    State& initial_state();

    std::tuple<unsigned int, unsigned int, State::Action> handle_attributes(unsigned int battery, unsigned int gold, const Room* position, std::list<const Room*>& mined);

private:
    State _initial_state;
    unsigned int _problem_size;
    std::list<const Room*> _mined;
};

#endif