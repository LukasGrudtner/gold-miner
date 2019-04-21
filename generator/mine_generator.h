#ifndef __MINE_GENERATOR_H__
#define __MINE_GENERATOR_H__

#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include <stdlib.h>

class MineGenerator
{
public:
    std::fstream generate(std::string filename, int size);
    std::vector<std::string> shuffle(int size);
};

#endif