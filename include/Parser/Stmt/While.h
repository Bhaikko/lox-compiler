#pragma once

#include "./Stmt.h"

namespace Stmt {
    class While: public Stmt 
    {
        public:
            Expr::Expr* condition;
            Stmt* body;

        public:
            While(Expr::Expr* condition, Stmt* body);

            virtual void* accept(Visitor<void*>* visitor) override;
    };
}