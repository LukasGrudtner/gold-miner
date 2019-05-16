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

    /* Attribute getter's. */
    Room*                   position();
    Action                  action()        const;
    unsigned int            battery()       const;
    unsigned int            gold()          const;
    std::string             coordinates()   const;
    std::list<const Room*>  mined_rooms();     /* List with the mined rooms by its ancestors states. */

    /* Returns a readable string to a given action list. */
    std::string actions_str(std::list<State::Action> actions) const;

    /* Returns a string to identifier the unicity of the state to the hash table. */
    std::string hash() const;

private:
    Room*                   _position   = nullptr;
    unsigned int            _battery    = 0;
    unsigned int            _gold       = 0;
    Action                  _action     = 0;
    std::list<const Room*>  _mined;
    std::string             _coordinates;
};

#endif