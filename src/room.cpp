#include "include/room.h"

Room::Room() {}

Room::Room(Goal goal)
{
    this->_goal = goal;
}

const Room* Room::left() const
{
    return this->_left;
}

const Room* Room::right() const
{
    return this->_right;
}

const Room* Room::forward() const
{
    return this->_forward;
}

const Room* Room::back() const
{
    return this->_back;
}

Room::Goal Room::goal() const
{
    return this->_goal;
}

void Room::set_left(Room* left)
{
    this->_left = left;
}

void Room::set_right(Room* right)
{
    this->_right = right;
}

void Room::set_forward(Room* forward)
{
    this->_forward = forward;
}

void Room::set_back(Room* back)
{
    this->_back = back;
}