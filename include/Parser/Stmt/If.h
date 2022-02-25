#pragma once

#include "./Stmt.h"

namespace Stmt {
    class If: public Stmt 
    {
        public:
            Expr::Expr* condition;
            Stmt* thenBranch;
            Stmt* elseBranch;
        public:
            If(Expr::Expr* condition, Stmt* thenBranch, Stmt* elseBranch);

            virtual void* accept(Visitor<void*>* visitor) override;
    };
}