#include "./../../include/Parser/Expr.h"

std::string Expr::accept(Visitor<std::string>* visitor)
{
    return "";
}

// template <class T>
std::string Visitor::visitBinaryExpr(Binary* expr)
{
    return "";
}

// template <class T>
std::string Visitor::visitGroupingExpr(Grouping* expr)
{
    return "";
}

// template <class T>
std::string Visitor::visitLiteralExpr(Literal* expr)
{
    return "";
}

// template <class T>
std::string Visitor::visitUnaryExpr(Unary* expr)
{
    return "";
}