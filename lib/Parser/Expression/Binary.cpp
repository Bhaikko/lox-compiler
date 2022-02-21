#include "./../../../include/Parser/Expression/Binary.h"

Expr::Binary::Binary(Expr* left, Token* operator_, Expr* right) 
{
    this->left = left;
    this->operator_ = operator_;
    this->right = right;
}

std::string* Expr::Binary::accept(Visitor<std::string*>* visitor)
{
    return visitor->visitBinaryExpr(this);
}
