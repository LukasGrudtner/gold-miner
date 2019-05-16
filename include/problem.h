#ifndef __PROBLEM_H__
#define __PROBLEM_H__

#include <list>
#include <tuple>
#include <vector>
#include <math.h>
#include <algorithm>
#include "state.h"

/* Define if the order of the successors will be random or not. */
// #define RANDOM_SUCCESSORS_CHOICE

/* Define the power of the battery according the problem's size. */
#define BATTERY_POWER 1.5

/* Instance of the problem. */
class Problem
{
public:
    /* Type definition of an Attribute (battery, gold, action list). */
    typedef std::tuple<unsigned int, unsigned int, State::Action> Attributes;
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

private:
    /* Handle the battery and gold values according the position and previous mined rooms. */
    Attributes handle_attributes(unsigned int battery, unsigned int gold, const Room* position, std::list<const Room*>& mined);

    /* Build the new state according its father, position and action. */
    State build_state(State& father, Room* new_position, State::Action action);

private:
    State           _initial_state;
    unsigned int    _problem_size;
};

#endif