/**
 * Author: Lukas Derner Grüdtner
 **/

#include "../include/heuristic.h"

Heuristic::Heuristic() {}

Heuristic::~Heuristic() {}

double Heuristic::value(Room* room) const
{
    std::vector<Pair> values;

    for (Pair pair : _values)
    {
        auto [r, distance] = pair;
        if (r == room)
        {
            return distance;
        }
    }
    return -1;
}