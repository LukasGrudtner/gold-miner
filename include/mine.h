#ifndef __MINE_H__
#define __MINE_H__

#include "include/room.h"

class Mine
{
public:
    /* Inits the mine with its size (n x n). */
    Mine(unsigned int size);
    ~Mine();

    /* Return the first room. */
    Room* entrance() const;

private:
    /* Size of the mine. */
    const unsigned int _size;

    /* Array with all the rooms of the mine. */
    Room* _rooms;
};

#endif