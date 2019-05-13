#include "../include/miner.h"

Miner::Miner(Room* position, unsigned int mine_size)
{
    this->_position = position;
    this->_mine_size = mine_size;
    this->_battery = pow(mine_size, BATTERY_POWER);
}

const Room* Miner::left()
{
    Room* next_room = _position->left();
    if (next_room)
        return move(next_room);

    return nullptr;
}

const Room* Miner::right()
{
    Room* next_room = _position->right();
    if (next_room)
        return move(next_room);

    return nullptr;
}

const Room* Miner::up()
{
    Room* next_room = _position->up();
    if (next_room)
        return move(next_room);

    return nullptr;
}

const Room* Miner::down()
{
    Room* next_room = _position->down();
    if (next_room)
        return move(next_room);

    return nullptr;
}

const Room* Miner::position() const
{
    return this->_position;
}

unsigned int Miner::battery() const
{
    return this->_battery;
}

unsigned int Miner::gold() const
{
    return this->_gold;
}

bool Miner::pick_gold()
{
    if (_position->pick_gold())
    {
        ++_gold;
        return true;
    }
    return false;
}

bool Miner::buy_battery()
{
    if (_gold)
    {
        --_gold;
        _battery += 5 * pow(_mine_size, BATTERY_POWER);
        return true;
    }
    return false;
}

Room* Miner::move(Room* next_room)
{
    if (next_room->goal() == Room::FENCE)
        return nullptr;

    if (_battery || buy_battery())
    {
        _position = next_room;
        --_battery;
    }
    
    return next_room;
}

const State Miner::dfs_limited(const unsigned int curl, const unsigned int maxl)
{
    State initial_state = State(_position, _battery, 0);
    Problem problem = Problem(initial_state);

    std::stack<State::Action>* actions = new std::stack<State::Action>();

    const State state = dfs_limited(curl, maxl, problem.initial_state(), problem, actions);

    return state;
}   

const State Miner::dfs_limited(const unsigned int curl, const unsigned int maxl, const State& state, const Problem& problem, std::stack<State::Action>* actions)
{
    if (problem.goal(state))
        return state;

    if (curl+1 == maxl)
        return state;
    else
    {
        actions->push(state.action());
        _explored_rooms++;

        for (const State s : problem.successors(state))
        {
            const State result = dfs_limited(curl+1, maxl, s, problem, actions);
            if (problem.goal(result))
                return result;
        }
    }
    return state;
}

unsigned int Miner::explored_rooms() const
{
    return _explored_rooms;
}