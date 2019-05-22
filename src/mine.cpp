/**
 * Author: Lukas Derner Grüdtner
 **/

#include "../include/mine.h"

Mine::Mine() {}

Mine::Mine(std::vector<Room*> rooms, unsigned int size)
{
    this->_size = size;
    
    this->_rooms = rooms;

    for (size_t i = 0; i < _rooms.size(); i++)
        draw_paths(_rooms[i], i);
}

Mine::~Mine() {}

Room* Mine::entrance() const
{
    return _rooms.front();
}

unsigned int Mine::size() const
{
    return this->_size;
}

void Mine::draw_paths(Room* room, unsigned int index)
{
    if (!case_first_line(index))
        room->set_up(_rooms[index-_size]);
    if (!case_first_column(index))
        room->set_left(_rooms[index-1]);
    if (!case_last_line(index))
        room->set_down(_rooms[index+_size]);
    if (!case_last_column(index))
        room->set_right(_rooms[index+1]);

    if (index < (_size*_size)-1)
        room->set_next(_rooms[index+1]);
}

/* Rooms that have no way up. */
bool Mine::case_first_line(unsigned int index)
{
    if (index < this->_size)
        return true;
    return false;
}

/*  Rooms that have no paths to the left. */
bool Mine::case_first_column(unsigned int index)
{
    if (index % this->_size == 0)
        return true;
    return false;
}

/*  Rooms that have no way down */
bool Mine::case_last_line(unsigned int index)
{
    if (index > (_size*_size - _size-1))
        return true;
    return false;
}

/* Rooms that have no path to the right. */
bool Mine::case_last_column(unsigned int index)
{
    if (index % _size == _size-1)
        return true;
    return false;
}