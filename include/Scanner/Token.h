#pragma once

#include <string>

#include "./TokenType.h"

class Token {
    public:
        TokenType type;
        std::string* lexeme;

        // This can be used as void*
        std::string* literal;
        int line;

    public:
        Token(TokenType type, std::string* lexeme, std::string* literal, int line);
        
    public:
    // Overloads
    friend std::ostream& operator<<(std::ostream& os, const Token& t);

};

