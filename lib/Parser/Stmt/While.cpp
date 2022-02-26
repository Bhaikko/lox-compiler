#include "./../../../include/Parser/Stmt/While.h"

Stmt::While::While(Expr::Expr* condition, Stmt* body)
{
    this->condition = condition;
    this->body = body;
}

void* Stmt::While::accept(Visitor<void*>* visitor)
{
    return visitor->visitWhileStmt(this);
}