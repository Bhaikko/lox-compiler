#pragma once

#include <string>
// #include "./Binary.h"
// #include "./Grouping.h"
// #include "./Literal.h"
// #include "./Unary.h"

class Binary;
class Grouping;
class Literal;
class Unary;

// "Visitor base class"
template <class T>
class Visitor 
{
    public:
        // Will be redefined in derived classes
        virtual T visitBinaryExpr(Binary* expr);
        virtual T visitGroupingExpr(Grouping* expr);
        virtual T visitLiteralExpr(Literal* expr);
        virtual T visitUnaryExpr(Unary* expr);

};

/**
 * @brief Base class that all expression classes will inherit fromW
 * 
 */
class Expr 
{
    public:
        virtual std::string accept(Visitor<std::string>* visitor);
};
