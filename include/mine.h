#ifndef __MINE_H__
#define __MINE_H__

#include <vector>
#include "room.h"

class Mine
{
public:
    /* Inits the mine with its size (n x n). */
    Mine(const std::vector<Room>& rooms, unsigned int size);

    /* Return the first room. */
    const Room* entrance() const;

private:
    void add_room(const Room& room);

private:
    /* Size of the mine. */
    unsigned int _size;

    /* Array with all the rooms of the mine. */
    std::vector<Room> _rooms;
};

#endif