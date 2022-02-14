#pragma once

#include <string>
#include <vector>

#include "./Expr.h"
#include "./Binary.h"
#include "./Grouping.h"
#include "./Literal.h"
#include "./Unary.h"

// class AstPrinter : public Visitor
class AstPrinter : public Visitor<std::string>
{
    public:
        std::string print(Expr* expr);

        virtual std::string visitBinaryExpr(Binary* expr) override;
        virtual std::string visitGroupingExpr(Grouping* expr) override;
        virtual std::string visitLiteralExpr(Literal* expr) override;
        virtual std::string visitUnaryExpr(Unary* expr) override;

    private:
        std::string parenthesize(std::string* name, std::vector<Expr*> exprs);
};

