#pragma once

#include <unordered_map>
#include <vector>

#include "./Token.h"

class Scanner {
    private:    
        // Field to track Scanner Position
        int start,      // points to first character of lexeme
            current,    // points to character being considered
            line;

        std::string source;
        std::vector<Token> tokens;

    public:
        Scanner(std::string source);
        std::vector<Token> scanTokens();

    private:
        bool isAtEnd();
};