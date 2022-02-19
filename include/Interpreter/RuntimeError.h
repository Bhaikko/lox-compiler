#pragma once

#include <stdexcept>

#include "./../Scanner/Token.h"

/**
 * @brief Class responsible for throwing runtime errors for interpreter
 * Inherits from std::runtime_error and stores other Error related attributes
 * 
 */
class RuntimeError: public std::runtime_error
{
    public:
        Token* token;

    public:
        RuntimeError(Token* token, std::string message);
};