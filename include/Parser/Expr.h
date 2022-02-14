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
// template <class T>
class Visitor 
{
    public:
        // Will be redefined in derived classes
        virtual std::string visitBinaryExpr(Binary* expr);
        virtual std::string visitGroupingExpr(Grouping* expr);
        virtual std::string visitLiteralExpr(Literal* expr);
        virtual std::string visitUnaryExpr(Unary* expr);

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
