#pragma once

#include "./Stmt.h"

namespace Stmt
{
    class Print: public Stmt
    {
        public:
            Expr::Expr* expression;

        public:
            Print(Expr::Expr* expression);

            virtual void* accept(Visitor<void*>* visitor) override;
    };
} 
