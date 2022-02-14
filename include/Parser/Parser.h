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
        Expr* expression();
        Expr* equality();
        Expr* comparison();
        Expr* term();
        Expr* factor();
        Expr* unary();

    private:
        bool match(std::vector<TokenType> tokenTypes);
        Token* previous();
        bool check(TokenType type);
        Token* advance();
        bool isAtEnd();
        Token* peek();
};