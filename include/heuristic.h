#ifndef __HEURISTIC_H__
#define __HEURISTIC_H__

#include <tuple>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include "mine.h"
#include "state.h"

/* Definition of an heuristic. */
class Heuristic
{
public:
    /* Pair of values: room and its distance to the nearest gold. */
    typedef std::tuple<Room*, double> Pair;

public:
    /* Heuristic constructor. */
    Heuristic();

    virtual ~Heuristic();

    /* Returns the heuristic value for a given room. */
    double value(Room* room) const;

private:
    /* Virtual method: build the heuristic values vector according the heuristic. */
    virtual void measure(Mine mine) = 0;

    /* Virtual method: measure the distance between two given rooms. */
    virtual double distance(const Room* x, const Room* y) const = 0;

protected:
    /* Vector of pairs <room, distance to the nearest gold>. */
    std::vector<Pair> _values;
};

#endif