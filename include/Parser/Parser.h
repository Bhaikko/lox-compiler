#pragma once

#include <vector>

#include "./../Lox.h"
#include "./../Scanner/Token.h"
#include "./Expression/ExpressionHeaders.h"
#include "./Stmt/StmtHeaders.h"
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
        Expr::Expr* expression();
        Expr::Expr* assignment();
        Expr::Expr* or_();
        Expr::Expr* and_();
        Expr::Expr* equality();
        Expr::Expr* comparison();
        Expr::Expr* term();
        Expr::Expr* factor();
        
        // Unary Operations
        Expr::Expr* unary();

        Expr::Expr* call();
        // Processes arguements of the function call
        Expr::Expr* finishCall(Expr::Expr* callee);

        // Literals Operations
        Expr::Expr* primary();

    // Statement Handling
    private:
        Stmt::Stmt* declaration();
        Stmt::Stmt* statement();
        Stmt::Stmt* printStatement();
        Stmt::Stmt* expressionStatment();
        Stmt::Stmt* ifStatement();
        Stmt::Stmt* whileStatement();
        /**
         * @brief This function converts a for loop statment into while loop
         * Hence, it does not require a syntax tree of its own.
         * 
         * @return Stmt::Stmt* 
         */
        Stmt::Stmt* forStatement();
        Stmt::Stmt* varDeclaration();
        Stmt::Stmt* classDeclaration();
        std::vector<Stmt::Stmt*>* block();
        Stmt::Stmt* function(std::string kind);
        Stmt::Stmt* returnStatement();

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