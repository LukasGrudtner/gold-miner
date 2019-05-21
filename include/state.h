/**
 * Author: Lukas Derner Grüdtner
 **/

#ifndef __STATE_H__
#define __STATE_H__

#include <list>
#include <string>
#include "room.h"

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
    State();
    State(Room* position, unsigned int battery, unsigned int gold);
    State(Room* position, unsigned int battery, unsigned int gold, const Action action, std::list<const Room*> mined);
    State(Room* position, unsigned int battery, unsigned int gold, const Action action, std::list<const Room*> mined, double h, double g, double value);

    /* Attribute getters and setters. */
    Room*               position()      const;
    Action              action()        const;
    unsigned int        battery()       const;
    unsigned int        gold()          const;
    Room::Coordinate    coordinate()    const;
    void                coordinate(Room::Coordinate coordinate);
    double              h()             const;
    double              g()             const;
    void                value(double value);

    std::list<const Room*>  mined_rooms();     /* List with the mined rooms by its ancestors states. */

    /* Returns a readable string to a given action list. */
    std::string actions_str(std::list<State::Action> actions) const;

    /* Returns a string to identifier the unicity of the state to the hash table. */
    std::string hash() const;

    std::string to_string() const
    {
        return "Battery: " + std::to_string(_battery) +
                "\nGold: " + std::to_string(_gold) + 
                "\nCoordinate: [" + std::to_string(std::get<0>(_coordinate)) + 
                ", " + std::to_string(std::get<1>(_coordinate)) + "]\n" +
                "\nh(): " + std::to_string(_heuristic_value) + 
                "\ng(): " + std::to_string(_g_value)+
                "\nvalue(): " + std::to_string(_value);
    }

    bool operator>(const State& state) const;
    bool operator<(const State& state) const;
    bool operator==(const State& state) const;

private:
    Room*                   _position   = nullptr;
    unsigned int            _battery    = 0;
    unsigned int            _gold       = 0;
    Action                  _action     = 0;
    std::list<const Room*>  _mined;
    Room::Coordinate        _coordinate;
    double                  _value              = 0;
    double                  _heuristic_value    = 0;
    unsigned int            _g_value            = 0;
};

#endif