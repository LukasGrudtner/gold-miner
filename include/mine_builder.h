#ifndef __MINE_BUILDER_H__
#define __MINE_BUILDER_H__

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "mine.h"

class MineBuilder
{
public:
    MineBuilder(std::string filepath);
    Mine build();

private:
    Room build_room(std::string condition);

private:
    std::string _filepath;
};

#endif