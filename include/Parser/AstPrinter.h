#pragma once

#include <string>
#include <vector>

#include "./Expression/ExpressionHeaders.h"

// class AstPrinter : public Visitor
class AstPrinter : public Expr::Visitor<std::string*>
{
    public:
        std::string* print(Expr::Expr* expr);

        virtual std::string* visitBinaryExpr(Expr::Binary* expr) override;
        virtual std::string* visitGroupingExpr(Expr::Grouping* expr) override;
        virtual std::string* visitLiteralExpr(Expr::Literal* expr) override;
        virtual std::string* visitUnaryExpr(Expr::Unary* expr) override;

    private:
        std::string* parenthesize(std::string* name, std::vector<Expr::Expr*> exprs);
};

