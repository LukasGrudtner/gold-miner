#ifndef __MINE_H__
#define __MINE_H__

#include <vector>
#include "room.h"

/**
 * [00][01][02][03]
 * [04][05][06][07]
 * [08][09][10][11]
 * [12][13][14][15]
 * 
 * Mine with 4x4 = 16 rooms.
 * Entrance = room 00.
 **/

class Mine
{
public:
    /* Inits the mine with its size (n x n). */
    Mine(Room* rooms, unsigned int size);

    /* Return the first room. */
    Room* entrance() const;

    /* Return mine's size. */
    unsigned int size() const;

private:
    void add_room(const Room& room);

    void draw_paths(Room* room, unsigned int index);

    bool case1(unsigned int index);
    bool case2(unsigned int index);
    bool case3(unsigned int index);
    bool case4(unsigned int index);

private:
    /* Size of the mine. */
    unsigned int _size;

    /* Array with all the rooms of the mine. */
    // std::vector<Room> _rooms;
    Room* _rooms;
};

#endif