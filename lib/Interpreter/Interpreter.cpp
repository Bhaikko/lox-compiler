#include "./../../include/Interpreter/Interpreter.h"

std::string* Interpreter::visitLiteralExpr(Literal* expr)
{
    return expr->value;
}

std::string* Interpreter::visitGroupingExpr(Grouping* expr)
{
    return evaluate(expr->expression);
}

std::string* Interpreter:: visitUnaryExpr(Unary* expr)
{
    std::string* right = evaluate(expr->right);

    // This is what that makes a language dynamically typed
    switch (expr->operator_->type) {
        case TokenType::MINUS:
            // return -string_to_double(right);
            *right = "-" + *right;
            return right;

        default:
            return nullptr;
            break;
    }
}

std::string* Interpreter::evaluate(Expr* expr)
{
    return expr->accept(this);
}

double Interpreter::string_to_double(std::string* literal)
{    
    return ::atof(literal->c_str());
}