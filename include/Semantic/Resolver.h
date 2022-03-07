#pragma once

#include <stack>
#include <unordered_map>

#include "./../Parser/Expression/ExpressionHeaders.h"
#include "./../Parser/Stmt/StmtHeaders.h"

class Interpreter;

enum FunctionType 
{
    NONE,
    FUNCTION
};

class Resolver: 
public Expr::Visitor<std::string*>,
public Stmt::Visitor<void*>
{
    private:
        // Keeping track whether or not the code is inside a function declaration
        FunctionType currentFunction;

    public:
        // Each element in stack represents a single block scope.
        // Scope stack is only for local block scopes
        // Global scope is not tracked by resolver
        std::stack<std::unordered_map<std::string, bool>*>* scopes;

    public: 
        Interpreter* interpreter;

    public:
        Resolver(Interpreter* interpreter);

    // Environment maps are read when we resolve variable expressions
    public:
        virtual std::string* visitAssignExpr(Expr::Assign* expr) override;
        virtual std::string* visitBinaryExpr(Expr::Binary* expr) override;
        virtual std::string* visitCallExpr(Expr::Call* expr) override;
        virtual std::string* visitGetExpr(Expr::Get* expr) override;
        virtual std::string* visitGroupingExpr(Expr::Grouping* expr) override;
        virtual std::string* visitLiteralExpr(Expr::Literal* expr) override;
        virtual std::string* visitLogicalExpr(Expr::Logical* expr) override;
        virtual std::string* visitUnaryExpr(Expr::Unary* expr) override;
        virtual std::string* visitVariableExpr(Expr::Variable* expr) override;

    public:
        virtual void* visitBlockStmt(Stmt::Block* stmt) override;
        virtual void* visitClassStmt(Stmt::Class* stmt) override;
        virtual void* visitExpressionStmt(Stmt::Expression* stmt) override;
        virtual void* visitFunctionStmt(Stmt::Function* stmt) override;
        virtual void* visitIfStmt(Stmt::If* stmt) override;
        virtual void* visitPrintStmt(Stmt::Print* stmt) override;
        virtual void* visitReturnStmt(Stmt::Return* stmt) override;
        virtual void* visitVarStmt(Stmt::Var* stmt) override;
        virtual void* visitWhileStmt(Stmt::While* stmt) override;

    public:
        void resolve(std::vector<Stmt::Stmt*>* statements);

    private:
        void beginScope();
        void endScope();
        void resolve(Stmt::Stmt* statement);
        void resolve(Expr::Expr* statement);
        void resolveLocal(Expr::Expr* expr, Token* name);
        void resolveFunction(Stmt::Function* stmt, FunctionType type);
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

/*
For other statements and expression,
visit methods are required to recurse down syntax tree but no 
declaration of variable and scopes required
*/
