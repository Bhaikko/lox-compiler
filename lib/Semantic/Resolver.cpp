#include "./../../include/Semantic/Resolver.h"

Resolver::Resolver(Interpreter* interpreter)
{
    this->interpreter = interpreter;

    scopes = new std::stack<std::unordered_map<std::string, bool>*>();

    this->currentFunction = FunctionType::NONE;
}


std::string* Resolver::visitVariableExpr(Expr::Variable* expr)
{
    // if (
    //     !scopes->empty() &&
    //     scopes->top()->at(*expr->name->lexeme) == false
    // ) {
    //     // Variable is declared but have not been defined
    //     // Therefore we throw an error
    //     Lox::error(
    //         expr->name,
    //         "Can't read local variable in its own initializer."
    //     );
    // }

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


std::string* Resolver::visitBinaryExpr(Expr::Binary* expr)
{
    resolve(expr->left);
    resolve(expr->right);

    return nullptr;
}

std::string* Resolver::visitCallExpr(Expr::Call* expr)
{
    resolve(expr->callee);

    for (Expr::Expr* argument: *expr->arguments) {
        resolve(argument);
    }

    return nullptr;
}

std::string* Resolver::visitGetExpr(Expr::Get* expr)
{
    // Since properties are looked up dynamically, they dont get resolved
    // During resolution, expression to the left is resolved only
    // Property access happens in interpreter
    resolve(expr->object);
    return nullptr;
}

std::string* Resolver::visitSetExpr(Expr::Set* expr)
{
    resolve(expr->value);
    resolve(expr->object);

    return nullptr;
}

std::string* Resolver::visitGroupingExpr(Expr::Grouping* expr)
{
    resolve(expr->expression);

    return nullptr;
}

std::string* Resolver::visitLiteralExpr(Expr::Literal* expr)
{
    // Literals expression doesnt mention any variables 
    // and doesnt contain any subexpresison

    return nullptr;
}

std::string* Resolver::visitLogicalExpr(Expr::Logical* expr)
{
    // Since short circuiting not considered in static analysis
    // We resolve both expressions

    resolve(expr->left);
    resolve(expr->right);

    return nullptr;
}

std::string* Resolver::visitUnaryExpr(Expr::Unary* expr)
{
    resolve(expr->right);
    return nullptr;
}

void* Resolver::visitClassStmt(Stmt::Class* stmt)
{
    declare(stmt->name);
    define(stmt->name);

    return nullptr;
}

void* Resolver::visitExpressionStmt(Stmt::Expression* stmt)
{
    resolve(stmt->expression);
    return nullptr;
}

void* Resolver::visitIfStmt(Stmt::If* stmt)
{
    // condition and both branches are resolved regardless of
    // condition evaluation
    resolve(stmt->condition);
    resolve(stmt->thenBranch);

    if (stmt->elseBranch != nullptr) {
        resolve(stmt->elseBranch);
    }

    return nullptr;
}

void* Resolver::visitPrintStmt(Stmt::Print* stmt)
{
    resolve(stmt->expression);
    return nullptr;
}

void* Resolver::visitReturnStmt(Stmt::Return* stmt)
{
    if (currentFunction == FunctionType::NONE) {
        Lox::error(stmt->keyword, "Cant't return from top-level code.");
    }

    if (stmt->value != nullptr) {
        resolve(stmt->value);
    }

    return nullptr;
}

void* Resolver::visitWhileStmt(Stmt::While* stmt)
{
    resolve(stmt->condition);
    resolve(stmt->body);

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

    resolveFunction(stmt, FunctionType::FUNCTION);
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

    // If there is collision when declaring variable in local scope
    // We throw error
    if (scope->find(*name->lexeme) != scope->end()) {
        Lox::error(name,
            "Already variable with this name in this scope."
        );
    }

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

void Resolver::resolveFunction(Stmt::Function* function, FunctionType type)
{
    // We keep track of enclosingFunction as local function can be defined
    // Hence, a track of 'how many' we're in is required
    FunctionType enclosingFunction = currentFunction;
    currentFunction = type;

    beginScope();

    for (Token* param: *function->params) {
        declare(param);
        define(param);
    }

    // In Static analysis, we immediately traverse into body 
    // In runtime, body was touched when the function was called
    resolve(function->body);

    endScope();
    currentFunction = enclosingFunction;
}