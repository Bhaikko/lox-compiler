#include "./../../../include/Parser/Stmt/Print.h"

Stmt::Print::Print(Expr* expression)
{
    this->expression = expression;
}

void* Stmt::Print::accept(Visitor<void*>* visitor)
{

}