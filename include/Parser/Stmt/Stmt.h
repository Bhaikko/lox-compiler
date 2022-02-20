#pragma once

#include <string>

#include "./../Expr.h"

class Print;
class Expression;

namespace Stmt {
    template <class T>
    class Visitor
    {
        public:
            virtual T visitPrintStmt(Print* stmt) { return T(); }
            virtual T visitExpressionStmt(Expression* stmt) { return T(); }
    };

    class Stmt
    {
        public:
            virtual void* accept(Visitor<void*>* visitor);
    };
}