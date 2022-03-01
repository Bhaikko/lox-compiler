#include "./../../../include/Parser/Stmt/Function.h"

Stmt::Function::Function(Token* name, std::vector<Token*>* params, std::vector<Stmt*>* body)
{
    this->name = name;
    this->params = params;
    this->body = body;
}

void* Stmt::Function::accept(Visitor<void*>* visitor)
{
    return visitor->visitFunctionStmt(this);
}