#include "../include/room.h"

Room::Room() {}

Room::Room(Goal goal)
{
    this->_goal = goal;
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
    if (this->_goal == Room::GOLD)
    {
        this->_goal = Room::FREEWAY;
        return true;
    }
    return false;
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

void Room::set_up(Room* up)
{
    this->_up = up;
}

void Room::set_down(Room* down)
{
    this->_down = down;
}