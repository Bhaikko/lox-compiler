#include "./../../../include/Parser/Expression/Logical.h"

Expr::Logical::Logical(Expr* left, Token* operator_, Expr* right)
{
    this->left = left;
    this->operator_ = operator_;
    this->right = right;
}

std::string* Expr::Logical::accept(Visitor<std::string*>* visitor)
{
    return visitor->visitLogicalExpr(this);
}