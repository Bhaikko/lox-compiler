#pragma once

#include <string>

/**
 * @brief Runtime Representation of Class in Lox
 * 
 */
class LoxClass 
{
    public:
        std::string* name;

    public:
        LoxClass(std::string* name);
};