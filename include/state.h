/**
 * Author: Lukas Derner Grüdtner
 **/

#ifndef __STATE_H__
#define __STATE_H__

#include <list>
#include <string>
#include "room.h"

/* Definition of a State. */
class State
{
public:
    /* Type definition of an Action (left, right, up, down or pick gold). */
    typedef unsigned char Action;
    static const Action LEFT        = (1 << 0); /*  1 */
    static const Action RIGHT       = (1 << 1); /*  2 */
    static const Action UP          = (1 << 2); /*  4 */
    static const Action DOWN        = (1 << 3); /*  8 */
    static const Action PICK_GOLD   = (1 << 4); /* 16 */

public:
    /* State's constructors. */
    State();
    State(Room* position, unsigned int battery, unsigned int gold);
    State(Room* position, unsigned int battery, unsigned int gold, const Action action, std::list<const Room*> mined);
    State(Room* position, unsigned int battery, unsigned int gold, const Action action, std::list<const Room*> mined, double h, double g, double f);

    /* Attribute getters and setters. */
    Room*               position()      const;
    Action              action()        const;
    unsigned int        battery()       const;
    unsigned int        gold()          const;
    Room::Coordinate    coordinate()    const;
    void                coordinate(Room::Coordinate coordinate);
    double              h()             const;
    double              g()             const;
    void                f(double f);

    /* Returns the lList with the mined rooms by its ancestors states. */
    std::list<const Room*> mined_rooms();     

    /* Returns a readable string to a given action list. */
    std::string actions_str(std::list<State::Action> actions) const;

    /* Returns a string to identifier the unicity of the state to the hash table. */
    std::string hash() const;

    /* Operators overload. */
    bool operator>  (const State& state) const;
    bool operator<  (const State& state) const;
    bool operator== (const State& state) const;

private:
    /* Pointer to a room. */
    Room* _position = nullptr;

    /* Miner's current battery. */
    unsigned int _battery = 0;

    /* Miner's current gold. */
    unsigned int _gold = 0;

    /* Action taken by the miner to reach this state. */
    Action _action = 0;

    /* List with the rooms mined by its ancestors. */
    std::list<const Room*> _mined;

    /* Tuple with the coordinates of the room. */
    Room::Coordinate _coordinate;

    /* Sum of h and g, when it is necessary. */
    double _f = 0;

    /* Heuristic value. */
    double _h = 0;

    /* Path cost since the first state. */
    unsigned int _g = 0;
};

#endif