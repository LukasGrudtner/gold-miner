/**
 * Author: Lukas Derner Grüdtner
 **/

#ifndef __MINE_BUILDER_H__
#define __MINE_BUILDER_H__

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "mine.h"

/* Class to build a mine according a given file. */
class MineBuilder
{
public:
    /* Mine builder constructor. */ 
    MineBuilder(std::string filepath);

    /* Build and returns the mine. */
    Mine build();

private:
    /* Build and return a individual room, according its condition. */
    Room build_room(std::string condition);

private:
    std::string _filepath;
};

#endif