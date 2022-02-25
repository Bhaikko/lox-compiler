#pragma once

#include <string>

#include "./../Expression/Expr.h"

namespace Stmt {
    class Print;
    class Expression;
    class Var;
    class Block;
    class If;
    
    template <class T>
    class Visitor
    {
        public:
            virtual T visitPrintStmt(Stmt::Print* stmt) { return T(); }
            virtual T visitExpressionStmt(Stmt::Expression* stmt) { return T(); }
            virtual T visitVarStmt(Stmt::Var* stmt) { return T(); }
            virtual T visitBlockStmt(Stmt::Block* stmt) { return T(); }
            virtual T visitIfStmt(Stmt::If* stmt) { return T(); }
    };

    class Stmt
    {
        public:
            virtual void* accept(Visitor<void*>* visitor);
    };
}