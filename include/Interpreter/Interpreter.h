#pragma once

#include "./../Parser/Expr.h"
#include "./../Parser/ExpressionHeaders.h"

class Interpreter: public Visitor<std::string*>
{
    public:
        virtual std::string* visitLiteralExpr(Literal* expr) override;
        virtual std::string* visitGroupingExpr(Grouping* expr) override;
        virtual std::string* visitUnaryExpr(Unary* expr) override;

    private:
        std::string* evaluate(Expr* expr);

    private:
        // Conversion methods from string to other datatypes
        // Converting String to double
        double string_to_double(std::string* literal);
    
};