#ifndef __STATE_H__
#define __STATE_H__

#include <string>
#include "room.h"
#include <list>
#include <math.h>

class State
{
public:

    typedef unsigned char Action;

    static const Action LEFT        = (1 << 0);
    static const Action RIGHT       = (1 << 1);
    static const Action UP          = (1 << 2);
    static const Action DOWN        = (1 << 3);
    static const Action PICK_GOLD   = (1 << 4);

    std::string _coord;

    State();
    State(Room* position, unsigned int battery, unsigned int gold);
    State(Room* position, const Action action, unsigned int battery, unsigned int gold, std::list<const Room*> mined);

    void merge_list(std::list<const Room*> mined);
    std::list<const Room*> mined_list();

    Room* position();
    unsigned int battery() const;
    unsigned int gold() const;
    Action action() const;

    std::string to_string() const;

private:
    Room*     _position = nullptr;
    unsigned int    _battery = 0;
    unsigned int    _gold = 0;
    Action          _action = 0;
    std::list<const Room*> _mined;
    
    
};

#endif