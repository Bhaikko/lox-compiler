#pragma once

#include <string>

#include "./TokenType.h"

class Token {
    private:
        TokenType type;
        std::string* lexeme;
        std::string* literal;
        int line;

    public:
        Token(TokenType type, std::string* lexeme, std::string* literal, int line);
        
    public:
    // Overloads
    friend std::ostream& operator<<(std::ostream& os, const Token& t);

};

