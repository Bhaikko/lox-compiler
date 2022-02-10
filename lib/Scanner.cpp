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

void Scanner::addToken(TokenType type)
{
    addToken(type, "");
}

void Scanner::addToken(TokenType type, std::string literal)
{
    std::string text = source.substr(start, current - start);
    tokens.push_back(Token(type, text, literal, line));
}

char Scanner::advance()
{
    current++;
    return source[current - 1];
}

void Scanner::scanToken()
{

}

bool Scanner::isAtEnd()
{
    return (unsigned)current >= source.length();
}
