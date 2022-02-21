#pragma once

#include "./Stmt.h"

namespace Stmt
{
    class Expression: public Stmt
    {
        public:
            Expr::Expr* expression;

        public:
            Expression(Expr::Expr* expression);

            virtual void* accept(Visitor<void*>* visitor) override;
    };
} 
