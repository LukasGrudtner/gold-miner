#include "../include/mine.h"

Mine::Mine(const std::vector<Room>& rooms, unsigned int size)
{
    this->_size = size;
    
    for (Room r : rooms)
        this->_rooms.push_back(r);

    for (unsigned int i = 0; i < this->_rooms.size(); i++)
        draw_paths(&(this->_rooms[i]), i);
}

const Room* Mine::entrance() const
{
    return &(this->_rooms[0]);
}

void Mine::draw_paths(Room* room, unsigned int index)
{
    if (!case1(index))
        room->set_back(&(this->_rooms[index-_size]));
    if (!case2(index))
        room->set_left(&(this->_rooms[index-1]));
    if (!case3(index))
        room->set_right(&(this->_rooms[index+1]));
    if (!case4(index))
        room->set_forward(&(this->_rooms[index+_size]));
}

/* Treats rooms that have no backward paths (first line, bottom to top) */
bool Mine::case1(unsigned int index)
{
    if (index < this->_size)
        return true;
    return false;
}

/*  Treats rooms that have no paths to the left (first column, left to right) */
bool Mine::case2(unsigned int index)
{
    if (index % this->_size == 0)
        return true;
    return false;
}

/*  Treats rooms that have no paths to the right (last column, left to right) */
bool Mine::case3(unsigned int index)
{
    if (index % _size == _size-1)
        return true;
    return false;
}

/* Treats rooms that have no paths up (last line, bottom to up) */
bool Mine::case4(unsigned int index)
{
    if (index > (_size * _size - _size - 1))
        return true;
    return false;
}


