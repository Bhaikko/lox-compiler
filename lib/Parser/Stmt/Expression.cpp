#include "./../../../include/Parser/Stmt/Expression.h"

Stmt::Expression::Expression(Expr* expression)
{
    this->expression = expression;
}

void* Stmt::Expression::accept(Visitor<void*>* visitor)
{
    return visitor->visitExpressionStmt(this);
}