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

Room* Room::next() const
{
    return this->_next;
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

Room::Coordinate Room::coordinate() const
{
    return this->_coordinate;
}

void Room::coordinate(Room::Coordinate coordinate)
{
    this->_coordinate = coordinate;
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

void Room::set_next(Room* next)
{
    this->_next = next;
}

bool Room::operator==(const Room& room) const
{
    return (this->_condition    == room._condition      &&
            this->_left         == room._left           &&
            this->_right        == room._right          &&
            this->_up           == room._up             &&
            this->_down         == room._down);
}