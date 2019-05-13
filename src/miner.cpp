#include "../include/miner.h"

Miner::Miner(Room* position, unsigned int mine_size)
{
    this->_position = position;
    this->_mine_size = mine_size;
    this->_battery = pow(mine_size, BATTERY_POWER);
    this->_problem = Problem(State(_position, _battery, 0));
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

#include <iostream>
const State Miner::dfs_limited(const unsigned int curl, const unsigned int maxl)
{
    std::list<State::Action> actions;
    std::unordered_map<std::string, bool> explored;

    const State state = dfs_limited(curl, maxl, _problem.initial_state(), _problem, actions, explored);

    std::cout << "buckets: " << explored.bucket_count() << std::endl;
    std::cout << "max buckets: " << explored.max_bucket_count() << std::endl;

    std::cout << "actions size: " << actions.size() << std::endl;

    std::string act;
    for (State::Action action : actions)
    {

        if (action == State::LEFT)
            act += "E -> ";
        else if (action == State::RIGHT)
            act += "D -> ";
        else if (action == State::DOWN)
            act += "B -> ";
        else if (action == State::UP)
            act += "C -> ";
    }

    std::cout << act << std::endl;

    return state;
}   

const State Miner::dfs_limited(const unsigned int curl, const unsigned int maxl, const State& state, const Problem& problem, std::list<State::Action>& actions, std::unordered_map<std::string, bool>& explored)
{
    if (problem.goal(state))
    {
        actions.push_front(state.action());
        return state;
    }

    if (curl+1 == maxl)
        return state;
    else
    {
        explored[state.to_string()] = true;

        _explored_rooms++;

        for (const State s : problem.successors(state))
        {
            if (!explored[s.to_string()])
            {
                const State result = dfs_limited(curl+1, maxl, s, problem, actions, explored);
                if (problem.goal(result))
                {
                    actions.push_front(state.action());
                    return result;
                }
            }
        }
    }
    return state;
}

unsigned int Miner::explored_rooms() const
{
    return _explored_rooms;
}

bool Miner::goal_state(const State& state) const
{
    return _problem.goal(state);
}