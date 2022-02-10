#include "./../include/Scanner.h"

Scanner::Scanner(std::string* source) 
{
    this->start = 0;
    this->current = 0;
    this->line = 1;

    this->source = source;
}

std::vector<Token*>* Scanner::scanTokens() 
{
    while (!isAtEnd()) {

        start = current;
        // scanToken();
    }

    // Adding End Of File
    tokens->push_back(new Token(TokenType::EOF_, nullptr, nullptr, line));
    return tokens;
}

void Scanner::addToken(TokenType type)
{
    addToken(type, nullptr);
}

void Scanner::addToken(TokenType type, std::string* literal)
{
    std::string text = source->substr(start, current - start);
    tokens->push_back(new Token(type, &text, literal, line));
}

char Scanner::advance()
{
    current++;
    return (*source)[current - 1];
}

void Scanner::scanToken()
{

}

bool Scanner::isAtEnd()
{
    return (unsigned)current >= source->length();
}
