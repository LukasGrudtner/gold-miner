/**
 * Author: Lukas Derner Grüdtner
 **/

#include "mine_generator.h"
#include <iostream>

int main(int argc, char* argv[])
{
    MineGenerator generator;
    
    if (argc != 3)
    {
        std::cout << "Missing arguments!" << std::endl;
        return 0;
    }

    generator.generate("input/generated/" + std::string(argv[1]) + ".mine", atoi(argv[2]));
    std::cout << "Mine " << std::string(argv[1]) << " generated successfully!" << std::endl;
}   