#include "../include/heuristic.h"

Heuristic::Heuristic(Mine mine)
{
    measure(mine);
}

// double Heuristic::value(Room* room) const
// {
//     std::vector<Pair> values;
//     double sum = 0;
//     size_t n = 0;

//     for (Pair pair : _heuristic_values)
//     {
//         auto [r, d] = pair;
//         if (r == room)
//         {
//             sum += d;
//             ++n;
//         }
//     }

//     return sum/n;
// }


double Heuristic::value(Room* room) const
{
    std::vector<Pair> values;

    for (Pair pair : _heuristic_values)
    {
        auto [r, distance] = pair;
        if (r == room)
        {
            return distance;
        }
    }
    return -1;
}


#include <iostream>
void Heuristic::measure(Mine mine)
{
    Room* room_i = mine.entrance();
    for (; room_i ; room_i = room_i->next())
    {
        double smallest_distance = 10e307;
        Pair pair;
        Room* room_k = mine.entrance();

        for (; room_k; room_k = room_k->next())
        {
            auto [x, y] = room_k->coordinate();

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
        _heuristic_values.push_back(pair);

        // auto [x,y] = room_i->coordinate();
        // std::cout << "[" << x << "," << y << "] (" << std::get<1>(pair) << ")" << std::endl;
    }
}

// void Heuristic::measure(Mine mine)
// {
//     Room* room_i = mine.entrance();
//     for (; room_i ; room_i = room_i->next())
//     {
//         double smallest_distance = 10e307;
//         Pair pair;
//         Room* room_k = mine.entrance();

//         for (; room_k; room_k = room_k->next())
//         {
//             auto [x, y] = room_k->coordinate();

//             if (room_k->condition() == Room::GOLD)
//             {
//                 Pair p = {room_i, distance(room_i, room_k)};
//                 _heuristic_values.push_back(pair);
//             }
//         }

//         // auto [x,y] = room_i->coordinate();
//         // std::cout << "[" << x << "," << y << "] (" << std::get<1>(pair) << ")" << std::endl;
//     }
// }

double Heuristic::distance(const Room* x, const Room* y) const
{
    auto [a1, b1] = x->coordinate();
    auto [a2, b2] = y->coordinate();

    return sqrt(pow((int)(a2-a1), 2) + pow((int)(b2-b1), 2));
}