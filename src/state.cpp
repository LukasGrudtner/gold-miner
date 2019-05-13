#include "../include/state.h"

State::State() {}

State::State(const Room* position, unsigned int battery, unsigned int gold)
{
    this->_position = position;
    this->_battery = battery;
    this->_gold = gold;
}

State::State(const Room* position, Action action, unsigned int battery, unsigned int gold)
{
    this->_position = position;
    this->_battery = battery;
    this->_gold = gold;
    this->_action = action;
}

const Room* State::position() const
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