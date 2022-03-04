#include "./../../include/Semantic/Resolver.h"

Resolver::Resolver(Interpreter* interpreter)
{
    this->interpreter = interpreter;

    scopes = new std::stack<std::unordered_map<std::string, bool>*>();
}


std::string* Resolver::visitVariableExpr(Expr::Variable* expr)
{
    if (
        !scopes->empty() &&
        scopes->top()->at(*expr->name->lexeme) == false
    ) {
        // Variable is declared but have not been defined
        // Therefore we throw an error
        Lox::error(
            expr->name,
            "Can't read local variable in its own initializer."
        );
    }

    resolveLocal(expr, expr->name);
    return nullptr;
}

std::string* Resolver::visitAssignExpr(Expr::Assign* expr)
{
    // Resolving the expression for the assigned variable
    resolve(expr->value);

    // resolve the variable thats being assigned to
    resolveLocal(expr, expr->name);

    return nullptr;
}

void* Resolver::visitVarStmt(Stmt::Var* stmt)
{
    // Binding done in two steps: Declaring and Defining 

    declare(stmt->name);
    if (stmt->initializer != nullptr) {
        resolve(stmt->initializer);
    }
    define(stmt->name);
    return nullptr;
}


void* Resolver::visitBlockStmt(Stmt::Block* stmt)
{
    beginScope();
    resolve(stmt->statements);
    endScope();

    return nullptr;
}

void* Resolver::visitFunctionStmt(Stmt::Function* stmt)
{
    // We declare and define function first then resolve its body
    // to support recursion to refer itself
    declare(stmt->name);
    define(stmt->name);

    resolveFunction(stmt);
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

void Resolver::resolveLocal(Expr::Expr* expr, Token* name)
{
    std::stack<std::unordered_map<std::string, bool>*>* tempScopes = 
        new std::stack<std::unordered_map<std::string, bool>*>();

    int depth = 0;      // Depth in scopes, where the variable is found
    while (!scopes->empty()) {
        if (
            scopes->top()->find(*name->lexeme) != 
            scopes->top()->end()
        ) {
            interpreter->resolve(expr, depth);
            break;
        } else {
            tempScopes->push(scopes->top());
            scopes->pop();
            depth++;
        }
    }

    // If the above whole loop runs and scopes becomes empty
    // Then the variable in the block is defined in Global scope

    // Trasfering all the traveresed scopes back to main scope
    while (!tempScopes->empty()) {
        scopes->push(tempScopes->top());
        tempScopes->pop();
    }

    delete tempScopes;
}

void Resolver::resolveFunction(Stmt::Function* function)
{
    beginScope();

    for (Token* param: *function->params) {
        declare(param);
        define(param);
    }

    // In Static analysis, we immediately traverse into body 
    // In runtime, body was touched when the function was called
    resolve(function->body);

    endScope();
}