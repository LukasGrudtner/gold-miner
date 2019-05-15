#include "../include/room.h"

Room::Room() {}

Room::Room(Condition condition)
{
    this->_condition = condition;
}

Room* Room::left() const
{
    return this->_left;
}

Room* Room::right() const
{
    return this->_right;
}

Room* Room::up() const
{
    return this->_up;
}

Room* Room::down() const
{
    return this->_down;
}

bool Room::pick_gold()
{
    if (this->_condition == Room::GOLD)
    {
        this->_condition = Room::FREE;
        return true;
    }
    return false;
}

Room::Condition Room::condition() const
{
    return this->_condition;
}

void Room::set_left(Room* left)
{
    this->_left = left;
}

void Room::set_right(Room* right)
{
    this->_right = right;
}

void Room::set_up(Room* up)
{
    this->_up = up;
}

void Room::set_down(Room* down)
{
    this->_down = down;
}

bool Room::operator==(const Room& room) const
{
    return (this->_condition    == room._condition      &&
            this->_left         == room._left           &&
            this->_right        == room._right          &&
            this->_up           == room._up             &&
            this->_down         == room._down);
}