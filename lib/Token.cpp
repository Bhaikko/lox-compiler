#include "../include/Token.h"

Token::Token(TokenType type, std::string lexeme, std::string literal, int line) 
{
    this->type = type;
    this->lexeme = lexeme;
    this->literal = literal;
    this->line = line;
}

std::ostream& operator<<(std::ostream& os, const Token& t) {
    os << t.type + " " + t.lexeme + " " + t.literal;
    return os;
}

