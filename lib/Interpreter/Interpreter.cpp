#include "./../../include/Interpreter/Interpreter.h"

std::string* Interpreter::visitLiteralExpr(Literal* expr)
{
    return expr->value;
}

std::string* Interpreter::visitGroupingExpr(Grouping* expr)
{
    return evaluate(expr->expression);
}

std::string* Interpreter::evaluate(Expr* expr)
{
    return expr->accept(this);
}