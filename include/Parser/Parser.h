#pragma once

#include <vector>

#include "./../Lox.h"
#include "./../Scanner/Token.h"
#include "./Expr.h"
#include "./ExpressionHeaders.h"
#include "./Stmt/Stmt.h"
#include "./Stmt/Print.h"
#include "./Stmt/Expression.h"
#include "./ParseError.h"

class Parser 
{
    private:
        std::vector<Token*>* tokens;
        int current = 0;

    public:
        Parser(std::vector<Token*>* tokens);
        std::vector<Stmt::Stmt*>* parse();

    // Expression handling
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

    // Statement Handling
    private:
        Stmt::Stmt* statement();
        Stmt::Stmt* printStatement();
        Stmt::Stmt* expressionStatment();
        
    private:
        bool match(std::vector<TokenType> tokenTypes);
        bool match(TokenType type);
        Token* previous();
        bool check(TokenType type);
        Token* advance();
        bool isAtEnd();
        Token* peek();
        Token* consume(TokenType type, std::string message);

        // This method returns a ParseError as it is upto the calling method
        // to decide whether to throw the error or report and move forward
        ParseError* error(Token* token, std::string message);

        // Skips current tokens till Next statement or certain keywords occur
        // This likely also skips cascaded errors
        void synchronize();

};