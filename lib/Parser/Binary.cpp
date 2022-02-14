#include "./../../include/Parser/Binary.h"

Binary::Binary(Expr* left, Token* operator_, Expr* right) 
{
    this->left = left;
    this->operator_ = operator_;
    this->right = right;
}

std::string Binary::accept(Visitor* visitor)
{
    return visitor->visitBinaryExpr(this);
}
