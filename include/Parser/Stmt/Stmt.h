#pragma once

#include <string>

#include "./../Expression/Expr.h"


namespace Stmt {
    class Print;
    class Expression;
    
    template <class T>
    class Visitor
    {
        public:
            virtual T visitPrintStmt(Stmt::Print* stmt) { return T(); }
            virtual T visitExpressionStmt(Stmt::Expression* stmt) { return T(); }
    };

    class Stmt
    {
        public:
            virtual void* accept(Visitor<void*>* visitor);
    };
}