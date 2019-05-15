#include "../include/miner.h"

Miner::Miner(Room* position, unsigned int mine_size)
{
    this->_position = position;
    this->_mine_size = mine_size;
    this->_battery = pow(mine_size, BATTERY_POWER);
    // this->_battery = 8;
    this->_problem = Problem(mine_size, State(_position, _battery, 0));
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
Miner::Answer Miner::dfs_limited(const unsigned int maxl)
{
    std::list<State::Action> actions;
    std::unordered_map<std::string, bool> explored;
    std::list<const Room*> mined;
    

    State state = dfs_limited(0, maxl, _problem.initial_state(), actions, explored);

    if (_problem.goal(state))
    {
        return {true, state, actions};
    }

    return {false, state, actions};
}   

State Miner::dfs_limited(const unsigned int curl, const unsigned int maxl, State& state, std::list<State::Action>& actions, std::unordered_map<std::string, bool>& explored)
{
    // std::cout << state.position()->coordenada() << "(b:" << state.battery() << ", g:" << state.gold() << ")" << " -> "

    if (_problem.goal(state))
    {
        actions.push_front(state.action());
        std::cout << std::to_string(state.action()) << state._coord << std::endl;
        return state;
    }

    if (curl+1 == maxl)
        return state;
    else
    {
        explored[state.to_string()] = true;

        _explored_rooms++;

        for (State s : _problem.successors(state))
        {
            if (!explored[s.to_string()])
            {
                State result = dfs_limited(curl+1, maxl, s, actions, explored);

                if (_problem.goal(result))
                {
                    actions.push_front(state.action());
                    return result;
                }          
                // std::cout << " <- ";      
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

Miner::Answer Miner::dfs_iterative(const unsigned int iterations)
{
    for (int i = 0; i <= iterations; i++)
    {
        auto [result, state, actions] = dfs_limited(i+1);
        if (result && _problem.goal(state))
            return {result, state, actions};
    }
    return {false, State(), std::list<State::Action>()};
}

std::string Miner::actions_str(std::list<State::Action> actions) const
{
    std::string str;
    for (auto action = actions.begin(); action != actions.end(); action++)
    {
        if      (*action & State::RIGHT) str += "D -> ";
        else if (*action & State::LEFT)  str += "E -> ";
        else if (*action & State::DOWN)  str += "B -> ";
        else if (*action & State:: UP)   str += "C -> ";

        if (*action & State::PICK_GOLD)
        {
            str += "PO"; 
            if (action != actions.begin() && action != std::prev(actions.end()))
                str += " -> ";
        } 
    }
    return str;
}

Miner::Result Miner::execute(Miner::SearchStrategy strategy, unsigned int parameter)
{
    auto [result, state, actions] = search(strategy, parameter);

    explore(actions);

    unsigned int score = 0;
    unsigned int explored_states = _explored_rooms;

    return {result, score, explored_states, actions};
}

Miner::Answer Miner::search(SearchStrategy strategy, unsigned int parameter)
{
    switch (strategy)
    {
    case Miner::DEEP_FIRST_SEARCH_ITERATIVE:
        return dfs_iterative(parameter);
    
    case Miner::DEEP_FIRST_SEARCH_LIMITED:
        return dfs_limited(parameter);
    }
}

void Miner::explore(std::list<State::Action> actions)
{
    for (State::Action action : actions)
    {
        if      (action & State::LEFT)  left();
        else if (action & State::RIGHT) right();
        else if (action & State::UP)    up();
        else if (action & State::DOWN)  down();
        if (action & State::PICK_GOLD)  pick_gold();
    }
}