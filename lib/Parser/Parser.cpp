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
    Expr::Expr* expr = or_();  // This falls to primary then returns IDENTIFIER

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

Expr::Expr* Parser::or_()
{
    Expr::Expr* expr = and_();

    while (match(TokenType::OR)) {
        Token* operator_ = previous();
        Expr::Expr* right = and_();

        expr = new Expr::Logical(expr, operator_, right);
    }

    return expr;
}

Expr::Expr* Parser::and_()
{
    Expr::Expr* expr = equality();

    while (match(TokenType::AND)) {
        Token* operator_ = previous();
        Expr::Expr* right = equality();

        expr = new Expr::Logical(expr, operator_, right);
    }

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

    return call();
}

Expr::Expr* Parser::call()
{
    Expr::Expr* expr = primary();

    while (true) {
        if (match(TokenType::LEFT_PAREN)) {
            // Processing arguments 
            // If left paren matched then its a function call
            // Call will be returned
            expr = finishCall(expr);
        } else {
            break;
        }
    }

    return expr;
}

Expr::Expr* Parser::finishCall(Expr::Expr* callee)
{
    std::vector<Expr::Expr*>* arguements = new std::vector<Expr::Expr*>();

    // Handling zero arguement case
    if (!check(TokenType::RIGHT_PAREN)) {
        // One arguement as expression required
        do {
            if (arguements->size() >= 255) {
                error(peek(), "Can't have more than 255 arguments.");
            }
            
            arguements->push_back(expression());
        } while (match(TokenType::COMMA));
    }

    Token* paren = consume(TokenType::RIGHT_PAREN, "Expect ')' after arguements.");

    return new Expr::Call(callee, paren, arguements);
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

    if (match(TokenType::FOR)) {
        return forStatement();
    }

    if (match(TokenType::IF)) {
        return ifStatement();
    }

    if (match(TokenType::WHILE)) {
        return whileStatement();
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

Stmt::Stmt* Parser::ifStatement()
{
    consume(TokenType::LEFT_PAREN, "Expect '(' after 'if'.");
    Expr::Expr* condition = expression();
    consume(TokenType::RIGHT_PAREN, "Expect ')' after if condition");

    Stmt::Stmt* thenBranch = statement();
    Stmt::Stmt* elseBranch = nullptr;

    // Nested Ifs handled with else bind to nearest preceding if
    if (match(TokenType::ELSE)) {
        elseBranch = statement();
    }

    return new Stmt::If(condition, thenBranch, elseBranch);
}

Stmt::Stmt* Parser::whileStatement()
{
    consume(TokenType::LEFT_PAREN, "Expect '(' after 'while'.");
    Expr::Expr* condition = expression();

    consume(TokenType::RIGHT_PAREN, "Expect ')' after condition.");
    Stmt::Stmt* body = statement();

    return new Stmt::While(condition, body);
}

Stmt::Stmt* Parser::forStatement()
{
    consume(TokenType::LEFT_PAREN, "Expect '(' after 'for'.");

    // Handling First Clause - Initializer
    // The below code differentiates between
    // Empty initialization, deleration or expression in first clause
    Stmt::Stmt* initializer;
    if (match(TokenType::SEMICOLON)) {
        initializer = nullptr;
    } else if (match(TokenType::VAR)) {
        initializer = varDeclaration();
    } else {
        initializer = expressionStatment();
    }

    // Handling Second Clause - condition
    Expr::Expr* condition = nullptr;
    // Checking if current Token isnt Semicolon
    // ie, there is an expression before semicolon token
    if (!check(TokenType::SEMICOLON)) {
        condition = expression();
    }
    consume(TokenType::SEMICOLON, "Expect ';' after loop condition.");
    
    // Handling Third Clause - increment
    Expr::Expr* increment = nullptr;
    if (!check(TokenType::RIGHT_PAREN)) {
        increment = expression();
    }
    // Increment in for always executes after the current body execution
    // Hence if increment exists, it will be attached at the end of body.

    consume(TokenType::RIGHT_PAREN, "Expect ')' after clauses.");

    Stmt::Stmt* body = statement();

    // Converting Parsed for loop sections into while loop (de-sugaring)

    // Attaching increment at end of body if it exists
    if (increment != nullptr) {
        std::vector<Stmt::Stmt*>* statements = new std::vector<Stmt::Stmt*>();
        statements->push_back(body);
        statements->push_back(new Stmt::Expression(increment));

        body = new Stmt::Block(statements);
    }

    // if no condition exists, set it as true
    if (condition == nullptr) {
        condition = new Expr::Literal(new std::string("true"));
    }

    // Converting the parsed for loop in while loop using
    // initialization, condition and body combined with increment
    body = new Stmt::While(condition, body);

    // If initializer exist
    // We create a block with initilization as its first statement
    // The envrioment related to that block will automatically be handled
    // by interpreter
    if (initializer != nullptr) {
        std::vector<Stmt::Stmt*>* statements = new std::vector<Stmt::Stmt*>();
        statements->push_back(initializer);
        statements->push_back(body);

        body = new Stmt::Block(statements);
    }

    return body;
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
        if (match(TokenType::FUN)) {
            return function("function");
        }

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

Stmt::Stmt* Parser::function(std::string kind)
{
    // Identifier token for function name
    Token* name = consume(TokenType::IDENTIFIER, "Expect " + kind + " name.");

    // Parsing the parameter list
    consume(TokenType::LEFT_PAREN, "Expect '(' after " + kind + " name.");
    std::vector<Token*>* parameters = new std::vector<Token*>();
    if (!check(TokenType::RIGHT_PAREN)) {
        do {
            if (parameters->size() >= 255) {
                error(peek(), "Can't have more than 255 parameters.");
            }

            parameters->push_back(consume(
                TokenType::IDENTIFIER, "Expect parameter name. "
            ));
        } while (match(TokenType::COMMA));
    }

    consume(TokenType::RIGHT_PAREN, "Expect ')' after paramters.");

    // Parsing Function Body
    consume(TokenType::LEFT_BRACE, "Expect '{' before " + kind + " body.");
    std::vector<Stmt::Stmt*>* body = block();

    return new Stmt::Function(name, parameters, body);
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
