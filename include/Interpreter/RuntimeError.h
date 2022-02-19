#pragma once

#include <stdexcept>

#include "./../Scanner/Token.h"

class RuntimeError: public std::runtime_error
{
    private:
        Token* token;

    public:
        RuntimeError(Token* token, std::string message);
};