/**
 * Author: Lukas Derner Grüdtner
 **/

#ifndef __MINE_BUILDER_H__
#define __MINE_BUILDER_H__

#include <tuple>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "mine.h"

/* Class to build a mine according a given file. */
class MineBuilder
{
public:
    /* Type definition of a tuple to init a mine. */
    typedef std::tuple<std::vector<Room*>, unsigned int> MineInit; 
public:
    /* Mine builder constructor. */ 
    MineBuilder(std::string filepath);

    /* Build and returns the mine. */
    MineInit build();

private:
    /* Build and return a individual room, according its condition. */
    Room* build_room(std::string condition);

private:
    std::string _filepath;
};

#endif