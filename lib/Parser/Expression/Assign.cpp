#include "./../../../include/Parser/Expression/Assign.h"

Expr::Assign::Assign(Token* name, Expr* value)
{
    this->name = name;
    this->value = value;
}

std::string* Expr::Assign::accept(Visitor<std::string*>* visitor)
{
    return visitor->visitAssignExpr(this);
}