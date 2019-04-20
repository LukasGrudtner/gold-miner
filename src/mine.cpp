#include "../include/mine.h"

Mine::Mine(const std::vector<Room>& rooms, unsigned int size)
{
    this->_size = size;
    
    for (Room r : rooms)
        this->_rooms.push_back(r);
}

const Room* Mine::entrance() const
{
    return &(this->_rooms[0]);
}

