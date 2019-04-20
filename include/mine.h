#ifndef __MINE_H__
#define __MINE_H__

#include "include/room.h"

class Mine
{
public:
    Mine(unsigned int size);
    ~Mine();

    Room* entrance() const;

private:
    const unsigned int _size;
    Room* _rooms;
};

#endif