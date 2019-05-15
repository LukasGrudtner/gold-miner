#include "../include/state.h"

State::State() {}

State::State(Room* position, unsigned int battery, unsigned int gold)
{
    this->_position = position;
    this->_battery = battery;
    this->_gold = gold;
}

State::State(Room* position, Action action, unsigned int battery, unsigned int gold, std::list<const Room*> mined)
{
    this->_position = position;
    this->_battery = battery;
    this->_gold = gold;
    this->_action = action;
    this->_mined = mined;
}

Room* State::position()
{
    return _position;
}

unsigned int State::battery() const
{
    return _battery;
}

unsigned int State::gold() const
{
    return _gold;
}

State::Action State::action() const
{
    return _action;
}

std::string State::to_string() const
{
    std::string explored_states;
    for (const Room* explored : _mined)
        explored_states += std::to_string((long unsigned int) explored);

    return std::to_string((long unsigned int) _position) + 
            std::to_string(_battery) +
            std::to_string(_gold) +
            explored_states;
    // return std::to_string((long unsigned int) _position);
}

void State::merge_list(std::list<const Room*> mined)
{
    for (const Room* room : mined)
        _mined.push_back(room);
}

std::list<const Room*> State::mined_list()
{
    return _mined;
}