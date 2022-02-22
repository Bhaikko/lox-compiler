#include "./../../../include/Parser/Stmt/Var.h"

Stmt::Var::Var(Token* token, Expr::Expr* initializer)
{
    this->name = token;
    this->initializer = initializer;
}

void* Stmt::Var::accept(Visitor<void*>* visitor)
{
    
}