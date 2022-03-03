#include "./../../include/Semantic/Resolver.h"

Resolver::Resolver(Interpreter* interpreter)
{
    this->interpreter = interpreter;

    scopes = new std::stack<std::unordered_map<std::string, bool>*>();
}


void* Resolver::visitVarStmt(Stmt::Var* stmt)
{
    // Binding done in two steps: Declaring and Defining 

    // declare(stmt->name);
    if (stmt->initializer != nullptr) {
        resolve(stmt->initializer);
    }
    // define(stmt->name);
    return nullptr;
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
    scopes->push(new std::unordered_map<std::string, bool>());
}

void Resolver::endScope()
{
    scopes->pop();
}

void Resolver::resolve(Stmt::Stmt* statement)
{
    statement->accept(this);
}

void Resolver::resolve(Expr::Expr* statement)
{
    statement->accept(this);
}

void Resolver::resolve(std::vector<Stmt::Stmt*>* statements)
{
    for (Stmt::Stmt* statement: *statements) {
        resolve(statement);
    }
}

void Resolver::declare(Token* name)
{
    if (scopes->empty()) {
        return;
    }

    std::unordered_map<std::string, bool>* scope = scopes->top();

    // Boolean related to string represents whether the variable
    // has finished resolving the initializer
    (*scope)[*name->lexeme] = false;
}

void Resolver::define(Token* name)
{
    if (scopes->empty()) {
        return;
    }

    // Variable fully initialised and available for use
    (*scopes->top())[*name->lexeme] = true;
}
