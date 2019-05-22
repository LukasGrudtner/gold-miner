/**
 * Author: Lukas Derner Grüdtner
 **/

#ifndef __MANHATTAN_H
#define __MANHATTAN_H

#include "heuristic.h"

/* Definition of the manhattan distance heuristic. */
class ManhattanDistance : public Heuristic
{
public:
    /* Manhattan distance constructor. */
    ManhattanDistance(Mine mine);

    ~ManhattanDistance();

private:
    /* Returns the distance between the two given rooms according the euclidian distance. */
    double distance(const Room* x, const Room* y) const;

    /* Build the values vector with the rooms of the mine and their distances. */
    void measure(Mine mine);
};

#endif