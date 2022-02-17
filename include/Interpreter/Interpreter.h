#pragma once

#include "./../Parser/Expr.h"
#include "./../Parser/ExpressionHeaders.h"

class Interpreter: public Visitor<std::string*>
{
    public:
        virtual std::string* visitLiteralExpr(Literal* expr) override;
        virtual std::string* visitGroupingExpr(Grouping* expr) override;

    private:
        std::string* evaluate(Expr* expr);
};