#ifndef __MINER_H__
#define __MINER_H__

#include "include/mine.h";
#include "include/room.h"

class Miner
{
public:
    Miner(const Mine& position);

    /* Methods to guide the miner inside the mine. */
    bool left();
    bool right();
    bool forward();
    bool back();

    /* Miner picks up the gold when possibile. */
    bool pickup();

    /* Attribute getter's. */
    unsigned int battery() const;
    unsigned int saved_gold() const;

private:
    unsigned int _battery;
    unsigned int _saved_gold;
    Room* position;
};

#endif