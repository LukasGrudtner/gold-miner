#ifndef __MINER_H__
#define __MINER_H__

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

    /* Attribute getter's. */
    unsigned int battery() const;
    unsigned int saved_gold() const;

private:
    unsigned int battery;
    unsigned int saved_gold;
};

#endif