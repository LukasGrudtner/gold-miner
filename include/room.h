#ifndef __ROOM_H__
#define __ROOM_H__

class Room
{
    

public:
    typedef unsigned char Goal;

    /* What the miner can find running through the rooms. */
    static const Goal FREEWAY = 0x00;
    static const Goal FENCE   = 0x01;
    static const Goal GOLD    = 0x02;

public:
    Room();
    Room(Goal goal);

    /* Possible paths and its rooms. */
    Room* left()    const;
    Room* right()   const;
    Room* up()      const;
    Room* down()    const;
    Goal goal()     const;
    bool pick_gold();


public:
    friend class Mine;

    /* Room setter's for Mine class use. */
    void set_left(Room* left);
    void set_right(Room* right);
    void set_up(Room* up);
    void set_down(Room* down);

private:
    Goal _goal;

    /* Pointers to adjacent rooms. */
    Room* _left     = nullptr;
    Room* _right    = nullptr;
    Room* _up  = nullptr;
    Room* _down     = nullptr;
};

#endif