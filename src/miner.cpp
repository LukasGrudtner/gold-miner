#include "../include/miner.h"

Miner::Miner(Room* position, unsigned int mine_size)
{
    this->_position = position;
    this->_mine_size = mine_size;
    this->_battery = pow(mine_size, BATTERY_POWER);
}

bool Miner::left()
{
    Room* next_room = this->_position->left();
    if (next_room != nullptr)
        return move(next_room);

    return false;
}

bool Miner::right()
{
    Room* next_room = this->_position->right();
    if (this->_position->right() != nullptr)
        return move(next_room);

    return false;
}

bool Miner::up()
{
    Room* next_room = this->_position->up();
    if (this->_position->up() != nullptr)
        return move(next_room);

    return false;
}

bool Miner::down()
{
    Room* next_room = this->_position->down();
    if (this->_position->down() != nullptr)
        return move(next_room);

    return false;
}

unsigned int Miner::battery() const
{
    return this->_battery;
}

unsigned int Miner::gold() const
{
    return this->_gold;
}

void Miner::pick_gold()
{
    ++(this->_gold);
}

bool Miner::buy_battery()
{
    if (this->_gold)
    {
        --(this->_gold);
        this->_battery += 5 * pow(_mine_size, BATTERY_POWER);
        return true;
    }
    return false;
}

bool Miner::move(Room* next_room)
{
    if (next_room->goal() == Room::FENCE)
        return false;

    if (this->_battery || buy_battery())
    {
        this->_position = next_room;
        --(this->_battery);
    }

    if (this->_position->goal() == Room::GOLD)
        _gold += this->_position->pick_gold();
    
    return true;
}