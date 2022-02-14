#pragma once

#include <vector>

#include "./../Scanner/Token.h"

class Parser 
{
    private:
        std::vector<Token>* tokens;
        int current = 0;

    public:
        Parser(std::vector<Token>* tokens);
};