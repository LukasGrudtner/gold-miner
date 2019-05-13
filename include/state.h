#ifndef __STATE_H__
#define __STATE_H__

#include <string>
#include "room.h"

class State
{
public:
    typedef unsigned char Action;

    static const Action LEFT        = 0x01;
    static const Action RIGHT       = 0x02;
    static const Action UP          = 0x03;
    static const Action DOWN        = 0x04;
    static const Action PICK_GOLD   = 0x05;

    State();
    State(const Room* position, unsigned int battery, unsigned int gold);
    State(const Room* position, const Action action, unsigned int battery, unsigned int gold);

    const Room* position() const;
    unsigned int battery() const;
    unsigned int gold() const;
    Action action() const;

private:
    const Room*     _position = nullptr;
    unsigned int    _battery = 0;
    unsigned int    _gold = 0;
    Action          _action = -1;
};

#endif