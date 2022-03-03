#pragma once

#include "./../Parser/Expression/ExpressionHeaders.h"
#include "./../Parser/Stmt/StmtHeaders.h"
#include "./../Interpreter/Interpreter.h"

class Resolver: 
public Expr::Visitor<void*>,
public Stmt::Visitor<void*>
{
    public: 
        Interpreter* interpreter;

    public:
        Resolver(Interpreter* interpreter);

    public:
        virtual void* visitBlockStmt(Stmt::Block* stmt) override;

    private:
        void beginScope();
        void endScope();
        void resolve(Stmt::Stmt* statement);
        void resolve(std::vector<Stmt::Stmt*>* statements);
};

/*
Nodes interesting when resolving variables
* A block statement introduces a new scope for the statements it contain
* A function declaration introduces a new scope for its body
    and binds its parameters in that scope
* A variable declaration adds a new variable to the current scope
* Variable and assignment expresions need to have their resolved
*/