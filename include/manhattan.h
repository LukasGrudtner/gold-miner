#ifndef __MANHATTAN_H
#define __MANHATTAN_H

#include "heuristic.h"

class ManhattanDistance : public Heuristic
{
public:
    ManhattanDistance(Mine mine);

private:
    void measure(Mine mine);
    double distance(const Room* x, const Room* y) const;
};

#endif