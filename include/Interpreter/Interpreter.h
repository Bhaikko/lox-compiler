#pragma once

#include <iostream>

#include "./../Parser/Expression/ExpressionHeaders.h"
#include "./../Parser/Stmt/StmtHeaders.h"
#include "./../Lox.h"
#include "./RuntimeHeaders.h"

class Interpreter: 
    public Expr::Visitor<std::string*>,
    public Stmt::Visitor<void*>
{
    public:
        // Holds fixed ref to outermost env.
        Environment* globals;
        // Tracks the current environment, 
        // Changes when entering and exiting scope
        Environment* environment;

        // Associates each syntax tree node with its resolved data
        std::unordered_map<Expr::Expr*, int>* locals;

    public:
        Interpreter();

    // Semantics handling for Expression and Statements
    // Expressions Handling
    public:
        virtual std::string* visitLiteralExpr(Expr::Literal* expr) override;
        virtual std::string* visitGroupingExpr(Expr::Grouping* expr) override;
        virtual std::string* visitUnaryExpr(Expr::Unary* expr) override;
        virtual std::string* visitBinaryExpr(Expr::Binary* expr) override;
        virtual std::string* visitVariableExpr(Expr::Variable* expr) override;
        virtual std::string* visitAssignExpr(Expr::Assign* expr) override;
        virtual std::string* visitLogicalExpr(Expr::Logical* expr) override;
        virtual std::string* visitCallExpr(Expr::Call* expr) override;

    // Statements Handling
    public:
        virtual void* visitPrintStmt(Stmt::Print* stmt) override;
        virtual void* visitExpressionStmt(Stmt::Expression* stmt) override;
        virtual void* visitVarStmt(Stmt::Var* stmt) override;
        virtual void* visitBlockStmt(Stmt::Block* stmt) override;
        virtual void* visitIfStmt(Stmt::If* stmt) override;
        virtual void* visitWhileStmt(Stmt::While* stmt) override;
        virtual void* visitFunctionStmt(Stmt::Function* stmt) override;
        virtual void* visitReturnStmt(Stmt::Return* stmt) override;

    private:
        // Resolver utilities
        void* lookUpVariable(Token* name, Expr::Expr* expr);
        void* getAt(int distance, std::string name);
        Environment* ancestor(int distance);

    private:
        // Evaluation of Every expression is done in post order
        std::string* evaluate(Expr::Expr* expr);
        std::string* isTruthy(std::string* object);

    public:
        void execute(Stmt::Stmt* stmt);
        void executeBlock(std::vector<Stmt::Stmt*>* statements, Environment* environment);

    private:
        // Error Handling based on semantics
        void checkNumberOperand(Token* operator_, std::string* operand);
        void checkNumberOperands(Token* operator_, std::string* left, std::string* right);

    private:
        // Conversion methods from string to other datatypes
        // Converting String to double
        double string_to_double(std::string* literal);
        bool isDouble(std::string* literal);
        bool isEqual(std::string* a, std::string* b);

    private:
        // Utilities
        std::string stringify(std::string* object);

    public:
        // Evaluates the expression and displays in proper format
        void interpret(std::vector<Stmt::Stmt*>* statements);
        void setupNativeFunctions();
        void resolve(Expr::Expr* expr, int depth);

    
};