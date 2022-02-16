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
        Token* operator_ = previous(); // Since match() consumes current token
        Expr* right = comparison();

        // Since comparison will always happen between two operators
        // Making a left associative binary expression
        // By having the prev expr on the left side of the binary expr
        expr = new Binary(expr, operator_, right);
    }

    return expr;
}

Expr* Parser::comparison() 
{
    Expr* expr = term();

    std::vector<TokenType> tokenTypes;
    tokenTypes.push_back(TokenType::GREATER);
    tokenTypes.push_back(TokenType::GREATER_EQUAL);
    tokenTypes.push_back(TokenType::LESS);
    tokenTypes.push_back(TokenType::LESS_EQUAL);

    while (match(tokenTypes)) {
        Token* operator_ = previous();
        Expr* right = term();

        expr = new Binary(expr, operator_, right);
    }

    return expr;
}

Expr* Parser::term() 
{
    Expr* expr = factor();
    
    std::vector<TokenType> tokenTypes;
    tokenTypes.push_back(TokenType::PLUS);
    tokenTypes.push_back(TokenType::MINUS);

    while (match(tokenTypes)) {
        Token* operator_ = previous();
        Expr* right = factor();

        expr = new Binary(expr, operator_, right);
    }

    return expr;
    
}

Expr* Parser::factor() 
{
    Expr* expr = unary();

    std::vector<TokenType> tokenTypes;
    tokenTypes.push_back(TokenType::SLASH);
    tokenTypes.push_back(TokenType::STAR);

    while (match(tokenTypes)) {
        Token* operator_ = previous();
        Expr* right = unary();

        expr = new Binary(expr, operator_, right);
    }

    return expr;

}

Expr* Parser::unary() 
{
    std::vector<TokenType> tokenTypes;
    tokenTypes.push_back(TokenType::BANG);
    tokenTypes.push_back(TokenType::BANG_EQUAL);

    if (match(tokenTypes)) {
        Token* operator_ = previous();
        Expr* right = unary();

        return new Unary(operator_, right);
    }

    return primary();
}

Expr* Parser::primary()
{
    if (match(TokenType::FALSE)) { return new Literal(new std::string("false")); }
    if (match(TokenType::TRUE)) { return new Literal(new std::string("true")); }
    if (match(TokenType::NIL)) { return new Literal(new std::string("nil")); }

    std::vector<TokenType> tokenTypes;
    tokenTypes.push_back(TokenType::NUMBER);
    tokenTypes.push_back(TokenType::STRING);

    if (match(tokenTypes)) {
        return new Literal(previous()->literal);
    }

    if (match(TokenType::LEFT_PAREN)) {
        Expr* expr = expression();
        consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");

        return new Grouping(expr);
    }
}

bool Parser::match(std::vector<TokenType> tokenTypes)
{
    for (TokenType type : tokenTypes) {
        // if (check(type)) {
        //     advance();
        //     return true;
        // }
        if (match(type)) {
            return true;
        }
    }

    return false;
}

bool Parser::match(TokenType type)
{
    if (check(type)) {
        advance();
        return true;
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

// Return most recently consumed token
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

// return current token without consuming it
Token* Parser::peek()
{
    return tokens->at(current);
}

Token* Parser::consume(TokenType type, std::string message)
{
    // If token matches the passed type, 
    // Parser consumes otherwise throws error
    if (check(type)) {
        return advance();
    }

    throw error(peek(), message);
}

ParseError* Parser::error(Token* token, std::string message)
{
    Lox::error(token, message);
    return new ParseError();
}

void Parser::synchronize()
{
    advance();

    while (!isAtEnd()) {
        if (previous()->type == TokenType::SEMICOLON) {
            return;
        }

        switch (peek()->type) {
            case TokenType::CLASS:
            case TokenType::FUN:
            case TokenType::VAR:
            case TokenType::FOR:
            case TokenType::IF:
            case TokenType::WHILE:
            case TokenType::PRINT:
            case TokenType::RETURN:
                return;
        }

        advance();
    }
}
