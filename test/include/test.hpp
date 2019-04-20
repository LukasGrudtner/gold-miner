#ifndef __TEST_HPP__
#define __TEST_HPP__

#include <iostream>
#include <string>

#include "console.hpp"

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

    void evaluate(const char* message);

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
    string ok   = string(BOLD) + "[" + GREEN_DARK + "OK" + CLEAR + BOLD + "]" + SPACE + message;
    string fail = string(BOLD) + "[" + RED_DARK + "FAILED" + CLEAR + BOLD + "]" + SPACE + message + " (ASSERT " + std::to_string(curr_assert) + ")";

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


void Test::evaluate(const char* message)
{
    result ? display(OK, message) : display(FAIL, message);
    clear();
}


#endif