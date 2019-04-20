#ifndef __MINE_H__
#define __MINE_H__

#include <vector>
#include "include/room.h"

using std::vector;

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