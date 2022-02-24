#include "./../../../include/Parser/Stmt/Block.h"

Stmt::Block::Block()
{
    this->statements = new std::vector<Stmt*>();
}

Stmt::Block::Block(std::vector<Stmt*>* statements)
{
    this->statements = statements;
}

void* Stmt::Block::accept(Visitor<void*>* visitor)
{
    return visitor->visitBlockStmt(this);
}