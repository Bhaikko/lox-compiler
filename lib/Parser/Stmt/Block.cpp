#include "./../../../include/Parser/Stmt/Block.h"

Stmt::Block::Block()
{
    this->statements = new std::vector<Stmt::Stmt*>();
}

Stmt::Block::Block(std::vector<Stmt::Stmt*>* statements)
{
    this->statements = statements;
}