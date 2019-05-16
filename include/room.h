/**
 * Author: Lukas Derner Grüdtner
 **/

#ifndef __ROOM_H__
#define __ROOM_H__

#include <string>

class Room
{
public:

    /* Type definition of a Codition, the state of the room that the miner can find. */
    typedef unsigned char Condition;
    static const Condition FREE = (1 << 0);
    static const Condition FENCE   = (1 << 1);
    static const Condition GOLD    = (1 << 2);

public:
    Room();
    Room(Condition condition);

    /* Possible paths and its rooms. */
    Room* left()            const;
    Room* right()           const;
    Room* up()              const;
    Room* down()            const;
    bool pick_gold();

    /* Condition of the room. */
    Condition condition()   const;

    /* Coordinates setters. */
    std::string coordinates() { return this->_coordinates; }
    void coordinates(std::string coord) { this->_coordinates = coord; }

    /* Overcharge equal operator. */
    bool operator==(const Room& room) const;

public:
    friend class Mine;

    /* Room setter's for Mine class use. */
    void set_left(Room* left);
    void set_right(Room* right);
    void set_up(Room* up);
    void set_down(Room* down);

private:
    Condition _condition;

    /* Pointers to adjacent rooms. */
    Room* _left     = nullptr;
    Room* _right    = nullptr;
    Room* _up       = nullptr;
    Room* _down     = nullptr;

    /* Just to facilitate the debug. */
    std::string _coordinates;
};

#endif