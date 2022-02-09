#include "./../include/Scanner.h"

Scanner::Scanner(std::string source) 
{
    this->start = 0;
    this->current = 0;
    this->line = 1;

    this->source = source;
}

std::vector<Token> Scanner::scanTokens() 
{
    while (!isAtEnd()) {

        start = current;
        // scanToken();
    }

    tokens.push_back(Token(TokenType::EOF_, "", "", line));
    return tokens;
}

bool Scanner::isAtEnd()
{
    return current >= source.length();
}
