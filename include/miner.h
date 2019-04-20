#ifndef __MINER_H__
#define __MINER_H__

#include <math.h>

#include "mine.h"
#include "room.h"

#define BATTERY_POWER 1.5

class Miner
{
public:
    /* Inits the miner in the mine's entrance. */
    Miner(const Room* position, unsigned int mine_size);

    /* Methods to guide the miner inside the mine. */
    bool left();
    bool right();
    bool forward();
    bool back();

    /* Attribute getter's. */
    unsigned int battery() const;
    unsigned int gold() const;

private:
    bool move(const Room* next_room);

    /* Miner picks up the gold when possibile. */
    void pick_gold();

    bool buy_battery();

private:
    /* Personal attributes of the miner. */
    unsigned int _battery   = 0;
    unsigned int _gold      = 0;
    unsigned int _mine_size = 0;

    /* Current position inside the mine. */
    const Room* _position = nullptr;
};

#endif