/**
 * Author: Lukas Derner Grüdtner
 **/

#ifndef __MINE_H__
#define __MINE_H__

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
    Mine();
    /* Inits the mine with its size (n x n). */
    Mine(Room* rooms, unsigned int size);

    /* Return the first room. */
    Room* entrance() const;

    /* Return mine's size. */
    unsigned int size() const;

private:
    /* Draw the paths inside the mine, linking them with pointers. */
    void draw_paths(Room* room, unsigned int index);

    /* Treats the cases of the rooms at the edge of the mine. */
    bool case_first_line    (unsigned int index);
    bool case_first_column  (unsigned int index);
    bool case_last_line     (unsigned int index);
    bool case_last_column   (unsigned int index);

private:
    /* Size of the mine. */
    unsigned int _size;

    /* Array with all the rooms of the mine. */
    Room* _rooms;
};

#endif