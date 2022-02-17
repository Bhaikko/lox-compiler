#include "./../../include/Parser/Expr.h"

std::string* Expr::accept(Visitor<std::string*>* visitor)
{
    return new std::string("");
}
