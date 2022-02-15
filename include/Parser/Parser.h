#pragma once

#include <vector>

#include "./../Scanner/Token.h"
#include "./Expr.h"
#include "./ExpressionHeaders.h"

class Parser 
{
    private:
        std::vector<Token*>* tokens;
        int current = 0;

    public:
        Parser(std::vector<Token*>* tokens);

    private:
        // Functions to parse Non Terminals
        // Binary Operations
        Expr* expression();
        Expr* equality();
        Expr* comparison();
        Expr* term();
        Expr* factor();
        
        // Unary Operations
        Expr* unary();

        // Literals Operations
        Expr* primary();

    private:
        bool match(std::vector<TokenType> tokenTypes);
        bool match(TokenType type);
        Token* previous();
        bool check(TokenType type);
        Token* advance();
        bool isAtEnd();
        Token* peek();
        void consume(TokenType type, std::string message);
};