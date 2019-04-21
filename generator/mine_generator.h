#ifndef __MINE_GENERATOR_H__
#define __MINE_GENERATOR_H__

#include <fstream>
#include <string>
#include <stdlib.h>

class MineGenerator
{
public:
    std::fstream generate(std::string filename, int size);
};

#endif