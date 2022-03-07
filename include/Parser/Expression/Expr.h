#pragma once

#include <string>

namespace Expr {
    class Binary;
    class Grouping;
    class Literal;
    class Unary;
    class Variable;
    class Assign;
    class Logical;
    class Call;
    class Get;
    class Set;

    // "Visitor base class"
    template <class T>
    class Visitor 
    {
        public:
            // Will be redefined in derived classes
            virtual T visitBinaryExpr(Binary* expr) { return T(); }
            virtual T visitGroupingExpr(Grouping* expr) { return T(); }
            virtual T visitLiteralExpr(Literal* expr) { return T(); }
            virtual T visitUnaryExpr(Unary* expr) { return T(); }
            virtual T visitVariableExpr(Variable* expr) { return T(); }
            virtual T visitAssignExpr(Assign* expr) { return T(); }
            virtual T visitLogicalExpr(Logical* expr) { return T(); }
            virtual T visitCallExpr(Call* expr) { return T(); }
            virtual T visitGetExpr(Get* expr) { return T(); }
            virtual T visitSetExpr(Set* expr) { return T(); }
    };

    /**
     * @brief Base class that all expression classes will inherit fromW
     * 
     */
    class Expr 
    {
        public:
            virtual std::string* accept(Visitor<std::string*>* visitor);
    };
}
