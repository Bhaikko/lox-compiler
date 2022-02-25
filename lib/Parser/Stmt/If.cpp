#include "./../../../include/Parser/Stmt/If.h"

Stmt::If::If(Expr::Expr* condition, Stmt* thenBranch, Stmt* elseBranch)
{   
    this->condition = condition;
    this->thenBranch = thenBranch;
    this->elseBranch = elseBranch;
}

void* Stmt::If::accept(Visitor<void*>* visitor) 
{
    return visitor->visitIfStmt(this);
}