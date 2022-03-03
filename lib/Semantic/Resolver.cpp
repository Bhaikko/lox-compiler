#include "./../../include/Semantic/Resolver.h"

Resolver::Resolver(Interpreter* interpreter)
{
    this->interpreter = interpreter;
}

void* Resolver::visitBlockStmt(Stmt::Block* stmt)
{
    beginScope();
    resolve(stmt->statements);
    endScope();

    return nullptr;
}

void Resolver::beginScope()
{

}

void Resolver::endScope()
{

}

void Resolver::resolve(Stmt::Stmt* statements)
{
    for (Stmt::Stmt* statement: *statements) {
        resolve(statement);
    }
}

void Resolver::resolve(std::vector<Stmt::Stmt*>* statements)
{

}
