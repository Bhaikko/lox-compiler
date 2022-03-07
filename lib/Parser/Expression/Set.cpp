#include "./../../../include/Parser/Expression/Set.h"

Expr::Set::Set(Expr* object, Token* name, Expr* value)
{
    this->object = object;
    this->name = name;
    this->value = value;
}

std::string* Expr::Set::accept(Visitor<std::string*>* visitor)
{
    return visitor->visitSetExpr(this);
}