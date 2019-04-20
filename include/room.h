#ifndef __ROOM_H__
#define __ROOM_H__

class Room
{
    typedef unsigned char Goal;

    /* What the miner can find running through the rooms. */
    static const Goal FREEWAY = 0x00;
    static const Goal FENCE   = 0x01;
    static const Goal GOLD    = 0x02;

    friend Mine;

public:
    Room(Goal goal);

    /* Possible paths and its rooms. */
    const Room* left()      const;
    const Room* right()     const;
    const Room* forward()   const;
    const Room* back()      const;

    Goal goal() const;

private:
    /* Room setter's for Mine class use. */
    void set_left(Room* left);
    void set_right(Room* right);
    void set_forward(Room* forward);
    void set_back(Room* back);

private:
    Goal _goal;

    /* Pointers to adjacent rooms. */
    Room* _left     = nullptr;
    Room* _right    = nullptr;
    Room* _forward  = nullptr;
    Room* _back     = nullptr;
};

#endif