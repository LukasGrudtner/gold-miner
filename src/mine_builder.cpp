#include "../include/mine_builder.h"

MineBuilder::MineBuilder(std::string filepath)
{
    this->_filepath = filepath;
}

Mine MineBuilder::build()
{
    std::string goal;
    std::ifstream file;
    std::vector<Room> rooms;
    unsigned int mine_size = 0;

    /* Open file. */
    file.open(this->_filepath);

    /* Read mine's size. */
    file >> mine_size;

    /* While the file doesn't end, build the room's vector. */
    while (!file.eof())
    {
        file >> goal;
        Room room = build_room(goal);
        rooms.push_back(room);
    }

    /* Close file. */
    file.close();

    return Mine(rooms, mine_size);
}

Room MineBuilder::build_room(std::string goal)
{
    Room room;
    if (goal == "0")
        room = Room(Room::FREEWAY);
    else if (goal == "1")
        room = Room(Room::FENCE);
    else
        room = Room(Room::GOLD);
    
    return room;
}