#include "./../../include/Parser/Expr.h"
// #include <iostream>

std::string Expr::accept(Visitor* visitor)
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