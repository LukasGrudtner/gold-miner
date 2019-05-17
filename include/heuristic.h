#ifndef __HEURISTIC_H__
#define __HEURISTIC_H__

#include <tuple>
#include <vector>
#include <math.h>
#include "mine.h"
#include "state.h"

class Heuristic
{
public:
    typedef std::tuple<Room*, double> Pair;

public:
    Heuristic(Mine mine);
    double value(Room* room) const;

private:
    void measure(Mine mine);
    double distance(const Room* x, const Room* y) const;

private:
    std::vector<Pair> _heuristic_values;
};

#endif