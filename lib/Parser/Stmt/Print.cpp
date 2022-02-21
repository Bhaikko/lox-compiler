#include "./../../../include/Parser/Stmt/Print.h"

Stmt::Print::Print(Expr::Expr* expression)
{
    this->expression = expression;
}

void* Stmt::Print::accept(Visitor<void*>* visitor)
{
    return visitor->visitPrintStmt(this);
}