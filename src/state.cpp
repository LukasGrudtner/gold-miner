#include "../include/state.h"

State::State() {}

State::State(Room* position, unsigned int battery, unsigned int gold)
{
    this->_position = position;
    this->_battery = battery;
    this->_gold = gold;
}

State::State(Room* position, unsigned int battery, unsigned int gold, Action action, std::list<const Room*> mined)
{
    this->_position = position;
    this->_battery = battery;
    this->_gold = gold;
    this->_action = action;
    this->_mined = mined;
}

State::State(Room* position, unsigned int battery, unsigned int gold, const Action action, std::list<const Room*> mined, double h, double g, double value)
{
    this->_position = position;
    this->_battery = battery;
    this->_gold = gold;
    this->_action = action;
    this->_mined = mined;
    this->_heuristic_value = h;
    this->_g_value = g;
    this->_value = value;
}

Room* State::position() const
{
    return _position;
}

State::Action State::action() const
{
    return _action;
}

unsigned int State::battery() const
{
    return _battery;
}

unsigned int State::gold() const
{
    return _gold;
}

Room::Coordinate State::coordinate() const
{
    return this->_coordinate;
}

void State::coordinate(Room::Coordinate coordinate)
{
    this->_coordinate = coordinate;
}

std::list<const Room*> State::mined_rooms()
{
    return _mined;
}

std::string State::actions_str(std::list<State::Action> actions) const
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

std::string State::hash() const
{
    std::string explored_states;
    for (const Room* explored : _mined)
        explored_states += std::to_string((long unsigned int) explored);

    return std::to_string((long unsigned int) _position) + 
            std::to_string(_battery) +
            std::to_string(_gold) +
            explored_states + 
            std::to_string(_heuristic_value) + 
            std::to_string(_g_value) + 
            std::to_string(_value);
}

double State::h() const
{
    return _heuristic_value;
}

bool State::operator>(const State& state) const
{
    return _value > state._value;
}

bool State::operator<(const State& state) const
{
    return _value < state._value;
}

bool State::operator==(const State& state) const
{
    return this->hash() == state.hash();
}

double State::g() const
{
    return _g_value;
}

void State::value(double value)
{
    this->_value = value;
}