#include "./../../../include/Parser/Stmt/Return.h"

Stmt::Return::Return(Token* keyword, Expr::Expr* value)
{
    this->keyword;
    this->value = value;
}

void* Stmt::Return::accept(Visitor<void*>* visitor)
{
    return visitor->visitReturnStmt(this);
}