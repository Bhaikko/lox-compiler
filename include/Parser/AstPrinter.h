#pragma once

#include <initializer_list>
#include <string>
#include <vector>

#include "./Expr.h"

class AstPrinter : public Visitor<std::string>
{
    public:
        std::string print(Expr* expr);

        virtual std::string visitBinaryExpr(Binary* expr) override;
        virtual std::string visitGroupingExpr(Grouping* expr) override;
        virtual std::string visitLiteralExpr(Literal* expr);
        virtual std::string visitUnaryExpr(Unary* expr);

    private:
        std::string parenthesize(std::string* name, std::vector<Expr*> exprs);
};

