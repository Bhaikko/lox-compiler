#pragma once

#include <iostream>

#include "./../Parser/Expr.h"
#include "./../Parser/ExpressionHeaders.h"
#include "./../Parser/Stmt/Stmt.h"
#include "./../Lox.h"

#include "./RuntimeError.h"

class Interpreter: 
    public Visitor<std::string*>,
    public Stmt::Visitor<void*>
{
    // Expressions Handling
    public:
        virtual std::string* visitLiteralExpr(Literal* expr) override;
        virtual std::string* visitGroupingExpr(Grouping* expr) override;
        virtual std::string* visitUnaryExpr(Unary* expr) override;
        virtual std::string* visitBinaryExpr(Binary* expr) override;

    // Statements Handling
    public:
        virtual void* visitExpressionStmt(Stmt::Expression* stmt);
        virtual void* visitPrintStmt(Stmt::Print* stmt);

    private:
        // Evaluation of Every expression is done in post order
        std::string* evaluate(Expr* expr);
        std::string* isTruthy(std::string* object);

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
        void interpret(Expr* expression);

    
};