#ifndef __MINER_H__
#define __MINER_H__

#include "include/mine.h";
#include "include/room.h"

class Miner
{
public:
    /* Methods to guide the miner inside the mine. */
    bool left();
    bool right();
    bool forward();
    bool back();

    /* Miner picks up the gold when possibile. */
    bool pickup();

    /* Enters the mine. */
    void enters(const Mine& mine) const;

    /* Attribute getter's. */
    unsigned int battery() const;
    unsigned int saved_gold() const;

private:
    unsigned int _battery;
    unsigned int _saved_gold;
    Room* location;
};

#endif