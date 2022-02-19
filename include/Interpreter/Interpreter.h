#pragma once

#include "./../Parser/Expr.h"
#include "./../Parser/ExpressionHeaders.h"

#include "./RuntimeError.h"

class Interpreter: public Visitor<std::string*>
{
    public:
        virtual std::string* visitLiteralExpr(Literal* expr) override;
        virtual std::string* visitGroupingExpr(Grouping* expr) override;
        virtual std::string* visitUnaryExpr(Unary* expr) override;
        virtual std::string* visitBinaryExpr(Binary* expr) override;

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

    
};