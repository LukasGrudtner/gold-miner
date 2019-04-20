#ifndef __CONSOLE_HPP__
#define __CONSOLE_HPP__

#include <iostream>

namespace console {
    #define BOLD "\x1B[1m"
    
    #define GREEN "\x1B[32m"
    #define GREEN_DARK "\x1B[38;2;0;145;0m"

    #define RED "\x1B[34m"
    #define RED_DARK "\x1B[38;2;195;0;0m"

    #define CLEAR "\x1B[0m"

    #define SPACE " "

    static void print(const char* message);
    
}

static void console::print(const char* message)
{
    std::cout << message << std::endl;
}

#endif