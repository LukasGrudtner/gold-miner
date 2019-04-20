#ifndef __CONSOLE_HPP__
#define __CONSOLE_HPP__

#include <iostream>

namespace console {
    static const char* BOLD = "\e[1m";
    
    static const char* GREEN = "\e[32m";
    static const char* GREEN_DARK = "\e[38;2;0;145;0m";

    static const char* RED = "\e[34m";
    static const char* RED_DARK = "\e[38;2;195;0;0m";

    static const char* CLEAR = "\e[0m";

    static const char* SPACE = " ";

    static void print(const char* message);
    
}

static void console::print(const char* message)
{
    std::cout << message << std::endl;
}

#endif