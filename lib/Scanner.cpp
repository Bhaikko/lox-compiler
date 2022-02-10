#include "./../include/Scanner.h"

Scanner::Scanner(std::string* source) 
{
    this->start = 0;
    this->current = 0;
    this->line = 1;

    this->source = source;

    tokens = new std::vector<Token*>();
}

std::vector<Token*>* Scanner::scanTokens() 
{
    while (!isAtEnd()) {

        start = current;
        scanToken();
    }

    // Adding End Of File
    tokens->push_back(new Token(TokenType::EOF_, nullptr, nullptr, line));
    return tokens;
}

void Scanner::addToken(TokenType type)
{
    addToken(type, nullptr);
}
#include <iostream>
void Scanner::addToken(TokenType type, std::string* literal)
{
    std::string* text = new std::string(source->substr(start, current - start));

    std::cout << *text << std::endl;

    tokens->push_back(new Token(type, text, literal, line));
}

char Scanner::advance()
{
    current++;
    return (*source)[current - 1];
}

void Scanner::scanToken()
{
    char c = advance();

    switch (c) {
        case '(': addToken(TokenType::LEFT_PAREN); break;
        case ')': addToken(TokenType::RIGHT_PAREN); break;
        case '{': addToken(TokenType::LEFT_BRACE); break;
        case '}': addToken(TokenType::RIGHT_BRACE); break;
        case ',': addToken(TokenType::COMMA); break;
        case '.': addToken(TokenType::DOT); break;
        case '-': addToken(TokenType::MINUS); break;
        case '+': addToken(TokenType::PLUS); break;
        case ';': addToken(TokenType::SEMICOLON); break;
        case '*': addToken(TokenType::STAR); break;

        default:
            // Error
            break;
    }
}

bool Scanner::isAtEnd()
{
    return (unsigned)current >= source->length();
}
