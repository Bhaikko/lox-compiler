#include "./../../include/Interpreter/Interpreter.h"

Interpreter::Interpreter()
{
    this->environment = new Environment();
}

std::string* Interpreter::visitLiteralExpr(Expr::Literal* expr)
{
    return expr->value;
}

std::string* Interpreter::visitGroupingExpr(Expr::Grouping* expr)
{
    return evaluate(expr->expression);
}

std::string* Interpreter::visitUnaryExpr(Expr::Unary* expr)
{
    std::string* right = evaluate(expr->right);

    // This is what that makes a language dynamically typed
    switch (expr->operator_->type) {
        case TokenType::MINUS:
            checkNumberOperand(expr->operator_, right);
            *right = "-" + *right;
            return right;

        case TokenType::BANG:
            
            return right;

        default:
            return nullptr;
            break;
    }
}

std::string* Interpreter::visitBinaryExpr(Expr::Binary* expr)
{
    std::string* left = evaluate(expr->left);
    std::string* right = evaluate(expr->right);

    switch (expr->operator_->type) {
        case TokenType::MINUS:
            checkNumberOperands(expr->operator_, left, right);
            return new std::string(std::to_string(
                string_to_double(left) - 
                string_to_double(right)
            ));

        case TokenType::SLASH:
            checkNumberOperands(expr->operator_, left, right);
            return new std::string(std::to_string(
                string_to_double(left) / 
                string_to_double(right)
            ));

        case TokenType::STAR:
            checkNumberOperands(expr->operator_, left, right);
            return new std::string(std::to_string(
                string_to_double(left) * 
                string_to_double(right)
            ));

        // Handles string concatenation and double addtion
        // If anyone one of operands is string then,
        // returns their concatenation
        case TokenType::PLUS:
            if (!isDouble(left) || !isDouble(right)) {
                return new std::string(*left + *right);
            }

            return new std::string(std::to_string(
                string_to_double(left) +
                string_to_double(right)
            ));

        case TokenType::GREATER:
            checkNumberOperands(expr->operator_, left, right);
            return new std::string(std::to_string(
                string_to_double(left) >
                string_to_double(right)
            ));

        case TokenType::GREATER_EQUAL:
            checkNumberOperands(expr->operator_, left, right);
            return new std::string(std::to_string(
                string_to_double(left) >=
                string_to_double(right)
            ));

        case TokenType::LESS:
            checkNumberOperands(expr->operator_, left, right);
            return new std::string(std::to_string(
                string_to_double(left) <
                string_to_double(right)
            ));

        case TokenType::LESS_EQUAL:
            checkNumberOperands(expr->operator_, left, right);
            return new std::string(std::to_string(
                string_to_double(left) <=
                string_to_double(right)
            ));

        case TokenType::BANG_EQUAL:
            return new std::string(std::to_string(
                !isEqual(left, right))
            );

        case TokenType::EQUAL_EQUAL:
            return new std::string(std::to_string(
                isEqual(left, right))
            );

        default:
            return nullptr;
    }
}

std::string* Interpreter::visitAssignExpr(Expr::Assign* expr)
{
    std::string* value = evaluate(expr->value);
    environment->assign(expr->name, value);

    return value;
}

std::string* Interpreter::visitVariableExpr(Expr::Variable* expr)
{
    return environment->get(expr->name);
}

void* Interpreter::visitExpressionStmt(Stmt::Expression* stmt)
{
    evaluate(stmt->expression);
    
    return nullptr;
}

void* Interpreter::visitPrintStmt(Stmt::Print* stmt)
{
    std::string* value = evaluate(stmt->expression);
    std::cout << stringify(value) << std::endl;

    return nullptr;
}

void* Interpreter::visitVarStmt(Stmt::Var* stmt)
{
    std::string* value = nullptr;

    if (stmt->initializer != nullptr) {
        value = evaluate(stmt->initializer);
    }

    environment->define(stmt->name->lexeme, value);
    return nullptr;
}

void* Interpreter::visitBlockStmt(Stmt::Block* stmt)
{
    executeBlock(stmt->statements, new Environment(environment));

    return nullptr;
}

void* Interpreter::visitIfStmt(Stmt::If* stmt)
{
    if (*isTruthy(evaluate(stmt->condition)) != "false") {
        execute(stmt->thenBranch);
    } else if (stmt->elseBranch != nullptr) {
        execute(stmt->elseBranch);
    }

    return nullptr;
}

void Interpreter::interpret(std::vector<Stmt::Stmt*>* statements)
{
    try {
        for (Stmt::Stmt* statement: *statements) {
            execute(statement);
        }
    } catch (RuntimeError error) {
        Lox::runtimeError(error);
    }
}

std::string Interpreter::stringify(std::string* object)
{
    if (object == nullptr) {
        return "nil";
    }

    // if (isDouble(object)) {
    //     if (object->substr(object->size() - 2, 2) == ".0") {
    //         return object->substr(0, object->size() - 2);
    //     }
    // }
    
    return *object;
}

void Interpreter::execute(Stmt::Stmt* stmt)
{
    stmt->accept(this);
}

void Interpreter::executeBlock(std::vector<Stmt::Stmt*>* statments, Environment* environment)
{
    Environment* previous = this->environment;

    try {
        this->environment = environment;

        for (Stmt::Stmt* statement: *statments) {
            execute(statement);
        }
    } catch (RuntimeError error) {
        Lox::runtimeError(error);
    } 

    this->environment = previous;
}

std::string* Interpreter::evaluate(Expr::Expr* expr)
{
    return expr->accept(this);
}

std::string* Interpreter::isTruthy(std::string* object)
{
    if (object == nullptr) {
        return new std::string("false");
    }

    // return "true" or "false" as is
    // Later handled by conversion methods
    return object;
}

double Interpreter::string_to_double(std::string* literal)
{    
    return ::atof(literal->c_str());
}

bool Interpreter::isDouble(std::string* literal)
{
    bool decimal = false;
    for (unsigned int i = 0; i < literal->size(); i++) {
        if (
            literal->at(i) < '0' || 
            literal->at(i) > '9'
        ) {
            if (literal->at(i) == '.') {
                if (decimal) {
                    return false;
                } else {
                    decimal = true;
                }
            } else {
                return false;
            }
        }
    }

    return true;
}

bool Interpreter::isEqual(std::string* a, std::string* b)
{
    if (a == nullptr && b == nullptr) {
        return true;
    }

    if (a == nullptr) {
        return false;
    }

    // May need to handle string equivalent too

    return a->at(0) == b->at(0);
}

void Interpreter::checkNumberOperand(Token* operator_, std::string* operand)
{
    if (isDouble(operand)) {
        return;
    }

    throw new RuntimeError(operator_, "Operand must be a number.");
}


void Interpreter::checkNumberOperands(Token* operator_, std::string* left, std::string* right)
{
    if (isDouble(left) && isDouble(right)) {
        return;
    }

    throw new RuntimeError(operator_, "Operands must be numbers.");
}
