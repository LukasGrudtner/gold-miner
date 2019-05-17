#include "../include/mine_builder.h"

MineBuilder::MineBuilder(std::string filepath)
{
    this->_filepath = filepath;
}

Mine MineBuilder::build()
{
    std::string goal;
    std::ifstream file;
    Room* rooms;
    unsigned int mine_size = 0;

    /* Open file. */
    file.open(this->_filepath);

    /* Read mine's size. */
    file >> mine_size;
    rooms = new Room[mine_size*mine_size];

    unsigned int counter = mine_size*mine_size;

    /* While the file doesn't end, build the room's vector. */
    unsigned int x = 0;
    unsigned int y = 0;
    while (counter--)
    {
        file >> goal;
        Room room = build_room(goal);

        room.coordinate({x, y});

        x++;

        if (x % mine_size == 0)
        {
            x = 0;
            y++;
        }

        rooms[(mine_size*mine_size)-counter-1] = room;
    }

    /* Close file. */
    file.close();

    return Mine(rooms, mine_size);
}

Room MineBuilder::build_room(std::string condition)
{
    Room room;
    if (condition == "0")
        room = Room(Room::FREE);
    else if (condition == "1")
        room = Room(Room::FENCE);
    else
        room = Room(Room::GOLD);
    
    return room;
}