/**
 * Author: Lukas Derner Grüdtner
 **/

#include "../include/manhattan.h"

ManhattanDistance::ManhattanDistance(Mine mine)
{
    measure(mine);
}

ManhattanDistance::~ManhattanDistance() {}

double ManhattanDistance::distance(const Room* x, const Room* y) const
{
    auto [a1, b1] = x->coordinate();
    auto [a2, b2] = y->coordinate();

    return abs((int) (a2-a1)) + abs((int) (b2-b1));
}

void ManhattanDistance::measure(Mine mine)
{
    Room* room_i = mine.entrance();
    for (; room_i ; room_i = room_i->next())
    {
        double smallest_distance = 10e307;
        Pair pair;
        Room* room_k = mine.entrance();

        for (; room_k; room_k = room_k->next())
        {
            if (room_k->condition() == Room::GOLD)
            {
                Pair p = {room_i, distance(room_i, room_k)};

                if (std::get<1>(p) < smallest_distance)
                {
                    smallest_distance = std::get<1>(p);
                    pair = p;
                }
            }
        }
        _values.push_back(pair);
    }
}