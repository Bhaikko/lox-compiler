#pragma once

#include <stack>
#include <unordered_map>

#include "./../Parser/Expression/ExpressionHeaders.h"
#include "./../Parser/Stmt/StmtHeaders.h"
#include "./../Interpreter/Interpreter.h"

class Resolver: 
public Expr::Visitor<std::string*>,
public Stmt::Visitor<void*>
{
    public:
        // Each element in stack represents a single block scope.
        // Scope stack is only for local block scopes
        // Global scope is not tracked by resolver
        std::stack<std::unordered_map<std::string, bool>*>* scopes;

    public: 
        Interpreter* interpreter;

    public:
        Resolver(Interpreter* interpreter);

    // public:


    public:
        virtual void* visitVarStmt(Stmt::Var* stmt) override;
        virtual void* visitBlockStmt(Stmt::Block* stmt) override;

    private:
        void beginScope();
        void endScope();
        void resolve(Stmt::Stmt* statement);
        void resolve(Expr::Expr* statement);
        void resolve(std::vector<Stmt::Stmt*>* statements);
        void declare(Token* name);
        void define(Token* name);
};

/*
Nodes interesting when resolving variables
* A block statement introduces a new scope for the statements it contain
* A function declaration introduces a new scope for its body
    and binds its parameters in that scope
* A variable declaration adds a new variable to the current scope
* Variable and assignment expresions need to have their resolved
*/