#include "./../../../include/Parser/Expression/Expr.h"

std::string* Expr::Expr::accept(Visitor<std::string*>* visitor)
{
    return new std::string("");
}
