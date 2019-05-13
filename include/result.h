#ifndef __RESULT_H__
#define __RESULT_H__

#include <unordered_map>
#include <stack>
#include <string>
#include "room.h"

class Result
{
public:

public:
    std::unordered_map <const Room*, const Room*> _explored;
    unsigned int _score = 0;
    std::stack<std::string> _actions;
};

#endif