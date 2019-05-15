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
    int y = 0;
    int x = 0;
    while (counter--)
    {
        file >> goal;
        Room room = build_room(goal);

        

        std::string coord = "[" + std::to_string(x) + "," + std::to_string(y) + "]";
        room.coordenadas(coord);

        y++;

        if (y % mine_size == 0)
        {
            y = 0;
            x++;
        }

        rooms[(mine_size*mine_size)-counter-1] = room;

        // std::cout << room.coordenadas() << std::endl;
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