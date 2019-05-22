#ifndef __EUCLIDIAN_H__
#define __EUCLIDIAN_H__

#include "heuristic.h"

/* Definition of the euclidian distance heuristic */
class EuclidianDistance : public Heuristic
{
public:
    /* Euclidian distance constructor. */
    EuclidianDistance(Mine mine);

private:
    /* Returns the distance between the two given rooms according the euclidian distance. */
    double distance(const Room* x, const Room* y) const;

    /* Build the values vector with the rooms of the mine and their distances. */
    void measure(Mine mine);
};

#endif