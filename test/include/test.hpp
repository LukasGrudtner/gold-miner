#ifndef __TEST_HPP__
#define __TEST_HPP__

#include <iostream>
#include <string>

#include "test/include/console.hpp"

typedef enum
{
    OK,
    FAIL
} Status;

using std::string;

class Test
{

public:
    void ASSERT_EQ(bool expression);
    void ASSERT_NOT(bool expression);

    bool evaluate(const char* message);

private:
    void clear();
    void display(Status status, const char* message);

private:
    bool result = true;
    int curr_assert = 0;
};

void Test::clear()
{
    result = true;
    curr_assert = 0;
}

void Test::display(Status status, const char* message)
{
    string ok   = string(console::BOLD) + "[" + string(console::GREEN_DARK) + "OK" + string(console::CLEAR) + string(console::BOLD) + "]" + string(console::SPACE) + message;
    string fail = string(console::BOLD) + "[" + string(console::RED_DARK) + "FAILED" + string(console::CLEAR) + string(console::BOLD) + "]" + string(console::SPACE) + message + " (ASSERT " + std::to_string(curr_assert) + ")";

    switch (status)
    {
        case OK:
            console::print(ok.c_str());
            break;
        
        case FAIL:
            console::print(fail.c_str());
            break;
    }
}

void Test::ASSERT_EQ(bool expression)
{
    if (result)
        curr_assert++;
    result = result && expression;
}

void Test::ASSERT_NOT(bool expression)
{
    if (result) 
        curr_assert++;
    
    result = result && !expression;
}


bool Test::evaluate(const char* message)
{
    result ? display(OK, message) : display(FAIL, message);
    clear();
}


#endif