/**
 * Author: Lukas Derner Grüdtner
 **/

#ifndef __ROOM_H__
#define __ROOM_H__

#include <tuple>
#include <string>

/* Definition of a position inside the mine. */
class Room
{
public:
    /* Type definition of a Codition, the state of the room that the miner can find. */
    typedef unsigned char Condition;
    static const Condition FREE  = (1 << 0);
    static const Condition FENCE = (1 << 1);
    static const Condition GOLD  = (1 << 2);

    /* Type definition of a Coordinate, a tuple of unsigned ints. */
    typedef std::tuple<unsigned int, unsigned int> Coordinate;

public:
    /* Room's constructors. */
    Room();
    Room(Condition condition);

    /* Possible paths and its rooms. */
    Room* left()        const;
    Room* right()       const;
    Room* up()          const;
    Room* down()        const;
    Room* next()        const;

    /* Pick gold action, remove the gold of the room. */
    bool pick_gold();

    /* Condition of the room. */
    Condition condition()   const;

    /* Coordinates setters. */
    Coordinate  coordinate() const;
    void        coordinate(Coordinate coordinate);

    /* Equal operator overload. */
    bool operator==(const Room& room) const;

public:
    /* Friend class, to access its private members. */
    friend class Mine;

    /* Room setter's for Mine class use. */
    void set_left(Room* left);
    void set_right(Room* right);
    void set_up(Room* up);
    void set_down(Room* down);
    void set_next(Room* room);

private:
    /* Condition of the room. */
    Condition _condition;

    /* Pointers to adjacent rooms. */
    Room* _left     = nullptr;
    Room* _right    = nullptr;
    Room* _up       = nullptr;
    Room* _down     = nullptr;
    Room* _next     = nullptr;

    /* Coordinates, just to facilitate the debug. */
    Coordinate _coordinate;
};

#endif