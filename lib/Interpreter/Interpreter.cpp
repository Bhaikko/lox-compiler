#include "./../../include/Interpreter/Interpreter.h"

std::string* Interpreter::visitLiteralExpr(Literal* expr)
{
    return expr->value;
}

std::string* Interpreter::visitGroupingExpr(Grouping* expr)
{
    return evaluate(expr->expression);
}

std::string* Interpreter::visitUnaryExpr(Unary* expr)
{
    std::string* right = evaluate(expr->right);

    // This is what that makes a language dynamically typed
    switch (expr->operator_->type) {
        case TokenType::MINUS:
            *right = "-" + *right;
            return right;

        case TokenType::BANG:
            
            return right;

        default:
            return nullptr;
            break;
    }
}

std::string* Interpreter::visitBinaryExpr(Binary* expr)
{
    std::string* left = evaluate(expr->left);
    std::string* right = evaluate(expr->right);

    switch (expr->operator_->type) {
        case TokenType::MINUS:
            return new std::string(std::to_string(
                string_to_double(left) - 
                string_to_double(right)
            ));

        case TokenType::SLASH:
            return new std::string(std::to_string(
                string_to_double(left) / 
                string_to_double(right)
            ));

        case TokenType::STAR:
            return new std::string(std::to_string(
                string_to_double(left) * 
                string_to_double(right)
            ));

        // Handles string concatenation and double addtion
        case TokenType::PLUS:
            if (!isDouble(left) || !isDouble(right)) {
                return new std::string(*left + *right);
            }

            return new std::string(std::to_string(
                string_to_double(left) +
                string_to_double(right)
            ));

        case TokenType::GREATER:
            return new std::string(std::to_string(
                string_to_double(left) >
                string_to_double(right)
            ));

        case TokenType::GREATER_EQUAL:
            return new std::string(std::to_string(
                string_to_double(left) >=
                string_to_double(right)
            ));

        case TokenType::LESS:
            return new std::string(std::to_string(
                string_to_double(left) <
                string_to_double(right)
            ));

        case TokenType::LESS_EQUAL:
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

std::string* Interpreter::evaluate(Expr* expr)
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