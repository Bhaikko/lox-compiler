#include "./../../include/Parser/Parser.h"

Parser::Parser(std::vector<Token*>* tokens)
{
    this->tokens = tokens;
}

Expr::Expr* Parser::expression()
{
    return assignment();
}

Expr::Expr* Parser::assignment()
{
    // Since, only one look ahead
    // we first treat l-value as expression and calculate it
    // Later it is recasted to decide if it Variable
    Expr::Expr* expr = equality();  // This falls to primary then returns IDENTIFIER

    if (match(TokenType::EQUAL)) {
        Token* equals = previous();
        Expr::Expr* value = assignment();

        // Checking if current expression is instance of Variable
        // Converting r-value expression to l-value representation
        if (Expr::Variable* e = dynamic_cast<Expr::Variable*>(expr)) {
            Token* name = e->name;
            return new Expr::Assign(name, value);
        }

        // If l-value as expression isn't valid assigment target
        // We report an error
        error(equals, "Invalid Assignment target.");
    }

    /*
        The end result of this trick is an assignment expression tree node
        that knows what it is assigning to and has an expression subtree for the value
        being assigned. All with only a single token of lookahead and no backtracking.
    */

    return expr;
}

std::vector<Stmt::Stmt*>* Parser::parse() 
{
    std::vector<Stmt::Stmt*>* statements = new std::vector<Stmt::Stmt*>();

    while (!isAtEnd()) {
        statements->push_back(declaration());
    }

    return statements;
}

Expr::Expr* Parser::equality() 
{
    Expr::Expr* expr = comparison();

    std::vector<TokenType> tokenTypes;
    tokenTypes.push_back(TokenType::BANG_EQUAL);
    tokenTypes.push_back(TokenType::EQUAL_EQUAL);

    while (match(tokenTypes)) {
        Token* operator_ = previous(); // Since match() consumes current token
        Expr::Expr* right = comparison();

        // Since comparison will always happen between two operators
        // Making a left associative binary expression
        // By having the prev expr on the left side of the binary expr
        expr = new Expr::Binary(expr, operator_, right);
    }

    return expr;
}

Expr::Expr* Parser::comparison() 
{
    Expr::Expr* expr = term();

    std::vector<TokenType> tokenTypes;
    tokenTypes.push_back(TokenType::GREATER);
    tokenTypes.push_back(TokenType::GREATER_EQUAL);
    tokenTypes.push_back(TokenType::LESS);
    tokenTypes.push_back(TokenType::LESS_EQUAL);

    while (match(tokenTypes)) {
        Token* operator_ = previous();
        Expr::Expr* right = term();

        expr = new Expr::Binary(expr, operator_, right);
    }

    return expr;
}

Expr::Expr* Parser::term() 
{
    Expr::Expr* expr = factor();
    
    std::vector<TokenType> tokenTypes;
    tokenTypes.push_back(TokenType::PLUS);
    tokenTypes.push_back(TokenType::MINUS);

    while (match(tokenTypes)) {
        Token* operator_ = previous();
        Expr::Expr* right = factor();

        expr = new Expr::Binary(expr, operator_, right);
    }

    return expr;
    
}

Expr::Expr* Parser::factor() 
{
    Expr::Expr* expr = unary();

    std::vector<TokenType> tokenTypes;
    tokenTypes.push_back(TokenType::SLASH);
    tokenTypes.push_back(TokenType::STAR);

    while (match(tokenTypes)) {
        Token* operator_ = previous();
        Expr::Expr* right = unary();

        expr = new Expr::Binary(expr, operator_, right);
    }

    return expr;

}

Expr::Expr* Parser::unary() 
{
    std::vector<TokenType> tokenTypes;
    tokenTypes.push_back(TokenType::BANG);
    tokenTypes.push_back(TokenType::BANG_EQUAL);

    if (match(tokenTypes)) {
        Token* operator_ = previous();
        Expr::Expr* right = unary();

        return new Expr::Unary(operator_, right);
    }

    return primary();
}

Expr::Expr* Parser::primary()
{
    if (match(TokenType::FALSE)) { return new Expr::Literal(new std::string("false")); }
    if (match(TokenType::TRUE)) { return new Expr::Literal(new std::string("true")); }
    if (match(TokenType::NIL)) { return new Expr::Literal(new std::string("nil")); }

    std::vector<TokenType> tokenTypes;
    tokenTypes.push_back(TokenType::NUMBER);
    tokenTypes.push_back(TokenType::STRING);

    if (match(tokenTypes)) {
        return new Expr::Literal(previous()->literal);
    }

    if (match(TokenType::IDENTIFIER)) {
        return new Expr::Variable(previous());
    }

    if (match(TokenType::LEFT_PAREN)) {
        Expr::Expr* expr = expression();
        consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");

        return new Expr::Grouping(expr);
    }

    // Token that cannot start an expression
    throw error(peek(), "Expect expression.");
}

/**
 * @brief Handles statements types
 * 
 * @return Stmt::Stmt* 
 */
Stmt::Stmt* Parser::statement()
{
    if (match(TokenType::PRINT)) {
        // PRINT consumed before calling this function
        return printStatement();
    }

    if (match(TokenType::LEFT_BRACE)) {
        return new Stmt::Block(block());
    }

    return expressionStatment();
}

Stmt::Stmt* Parser::printStatement()
{
    Expr::Expr* value = expression();
    consume(TokenType::SEMICOLON, "Expect ';' after value. ");

    return new Stmt::Print(value);
}

Stmt::Stmt* Parser::expressionStatment()
{
    Expr::Expr* expr = expression();
    consume(TokenType::SEMICOLON, "Expect ';' after expression. ");

    return new Stmt::Expression(expr);
}

std::vector<Stmt::Stmt*>* Parser::block()
{
    std::vector<Stmt::Stmt*>* statements = new std::vector<Stmt::Stmt*>();

    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        statements->push_back(declaration());
    }

    consume(TokenType::RIGHT_BRACE, "Expect '}' after block.");
    return statements;
}


Stmt::Stmt* Parser::declaration()
{
    try {
        if (match(TokenType::VAR)) {
            return varDeclaration();
        }

        return statement();
    } catch (ParseError error) {
        // Parser goes into Panic mode and skips token
        // Till valid token is found
        synchronize();

        return nullptr;
    }
}

Stmt::Stmt* Parser::varDeclaration()
{
    Token* name = consume(TokenType::IDENTIFIER, "Expect variable name.");

    Expr::Expr* initializer = nullptr;
    if (match(TokenType::EQUAL)) {
        initializer = expression();
    }

    consume(TokenType::SEMICOLON, "Expect ';' after variable declaration");

    return new Stmt::Var(name, initializer);
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
            default: 
                break;
        }

        advance();
    }
}
