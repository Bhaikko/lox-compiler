#include "./../../include/Parser/Parser.h"

Parser::Parser(std::vector<Token*>* tokens)
{
    this->tokens = tokens;
}

Expr* Parser::expression()
{
    return equality();
}

Expr* Parser::equality() 
{
    Expr* expr = comparison();

    std::vector<TokenType> tokenTypes;
    tokenTypes.push_back(TokenType::BANG_EQUAL);
    tokenTypes.push_back(TokenType::EQUAL_EQUAL);

    while (match(tokenTypes)) {
        Token* operator_ = previous();
        Expr* right = comparison();

        // Since comparison will always happen between two operators
        expr = new Binary(expr, operator_, right);
    }

    return expr;
}

Expr* Parser::comparison() 
{

}

Expr* Parser::term() 
{

}

Expr* Parser::factor() 
{

}

Expr* Parser::unary() 
{

}

bool Parser::match(std::vector<TokenType> tokenTypes)
{
    for (TokenType type : tokenTypes) {
        if (check(type)) {
            advance();
            return true;
        }
    }

    return false;
}

bool Parser::check(TokenType type) 
{
    if (isAtEnd()) {
        return false;
    }

    return peek()->type == type;
}

Token* Parser::previous()
{
    return tokens->at(current - 1);
}

Token* Parser::advance()
{
    if (!isAtEnd()) {
        current++;
    }

    return previous();
}

bool Parser::isAtEnd()
{
    return peek()->type == TokenType::EOF_;
}

Token* Parser::peek()
{
    return tokens->at(current);
}