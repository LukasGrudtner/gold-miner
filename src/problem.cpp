#include "../include/problem.h"

Problem::Problem(const State& initial_state)
{
    this->_initial_state = initial_state;
}

std::list<const State> Problem::successors(const State& state) const
{
    std::list<const State> successors;

    const Room* position = state.position();

    if (state.battery())
    {
        if (position->left())
        {
            State left = State(position->left(), State::LEFT, state.battery()-path_cost(), state.gold());
            successors.push_back(left);
        }
        if (position->right())
        {
            State right = State(position->right(), State::RIGHT, state.battery()-path_cost(), state.gold());
            successors.push_back(right);
        }
        if (position->up())
        {
            State up = State(position->up(), State::UP, state.battery()-path_cost(), state.gold());
            successors.push_back(up);
        }
        if (position->down())
        {
            State down = State(position->down(), State::DOWN, state.battery()-path_cost(), state.gold());
            successors.push_back(down);
        }
    }
    return successors;
}

bool Problem::goal(const State& state) const
{
    return state.position()->goal() == Room::GOLD;
}

unsigned int Problem::path_cost() const
{
    return 1;
}

const State& Problem::initial_state() const
{
    return this->_initial_state;
}