#include "./../../../include/Parser/Stmt/Class.h"

Stmt::Class::Class(Token* name, std::vector<Function*>* methods)
{
    this->name = name;
    this->methods = methods;
}

void* Stmt::Class::accept(Visitor<void*>* visitor)
{
    return visitor->visitClassStmt(this);
}

