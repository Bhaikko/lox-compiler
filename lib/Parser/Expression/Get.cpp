#include "./../../../include/Parser/Expression/Get.h"

Expr::Get::Get(Expr* object, Token* name)
{
    this->object = object;
    this->name = name;
}

std::string* Expr::Get::accept(Visitor<std::string*>* visitor)
{
    return visitor->visitGetExpr(this);
}