#pragma once

#include <stdexcept>
#include <string>

class ParseError: public std::runtime_error
{
    public:
        ParseError();
};