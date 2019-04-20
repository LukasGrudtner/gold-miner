#ifndef __ROOM_H__
#define __ROOM_H__

class Room
{
    typedef unsigned char Goal;

    static const Goal FREEWAY = 0x00;
    static const Goal FENCE   = 0x01;
    static const Goal GOLD    = 0x02;

public:
    Room(Goal target);

    const Room* left() const;
    const Room* right() const;
    const Room* forward() const;
    const Room* back() const;

    Goal goal() const;

private:
    Goal _goal;

    Room* _left;
    Room* _right;
    Room* _forward;
    Room* _back;
};

#endif