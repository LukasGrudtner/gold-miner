#ifndef __PROBLEM_H__
#define __PROBLEM_H__

#include <list>
#include "state.h"

class Problem
{
public:
    Problem();
    Problem(const State& initial_state);

    /* Return a list of successors states for a given state. */
    std::list<const State> successors(const State& state) const;

    /* Checks if the given state is a target. */
    bool goal(const State& state) const;

    /* Return the path cost of the problem. */
    unsigned int path_cost() const;

    /* Returns the initial state. */
    const State& initial_state() const;

private:
    State _initial_state;
};

#endif