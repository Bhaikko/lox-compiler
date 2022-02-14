#include "./../../include/Parser/AstPrinter.h"

std::string AstPrinter::print(Expr* expr)
{
    return expr->accept(this);
}

std::string AstPrinter::parenthesize(std::string* name, std::vector<Expr*> exprs) 
{
    std::string builder = "(";
    builder += *name;
    for (Expr* expr: exprs) {
        builder += " ";
        builder += expr->accept(this);
    }

    builder += ")";

    return builder;
}

std::string AstPrinter::visitBinaryExpr(Binary* expr) 
{
    std::vector<Expr*> exprs;
    exprs.push_back(expr->left);
    exprs.push_back(expr->right);

    return parenthesize(
        expr->operator_->lexeme, exprs
    );
}

std::string AstPrinter::visitGroupingExpr(Grouping* expr) 
{
    std::vector<Expr*> exprs;
    exprs.push_back(expr->expression);

    return parenthesize(new std::string("group"), exprs);
}

std::string AstPrinter::visitLiteralExpr(Literal* expr) 
{
    if (expr->value->size() == 0) {
        return "nil";
    }
    return *(expr->value);

}

std::string AstPrinter::visitUnaryExpr(Unary* expr) 
{
    std::vector<Expr*> exprs;
    exprs.push_back(expr->right);

    return parenthesize(expr->operator_->lexeme, exprs);
}
