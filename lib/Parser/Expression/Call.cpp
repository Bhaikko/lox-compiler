#include "./../../../include/Parser/Expression/Call.h"

Expr::Call::Call(Expr* callee, Token* paren, std::vector<Expr*>* arguments)
{
    this->callee = callee;
    this->paren = paren;
    this->arguments = arguments;
}

std::string* Expr::Call::accept(Visitor<std::string*>* visitor)
{
    return visitor->visitCallExpr(this);
}