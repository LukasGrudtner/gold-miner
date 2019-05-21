#ifndef __HEURISTIC_H__
#define __HEURISTIC_H__

#include <tuple>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include "mine.h"
#include "state.h"

class Heuristic
{
public:
    typedef std::tuple<Room*, double> Pair;

public:
    Heuristic();
    double value(Room* room) const;

private:
    virtual void measure(Mine mine) = 0;
    virtual double distance(const Room* x, const Room* y) const = 0;

protected:
    std::vector<Pair> _heuristic_values;
};

#endif