#pragma once

#include "./Stmt.h"

namespace Stmt
{
    class Print: public Stmt
    {
        public:
            Expr* expression;

        public:
            Print(Expr* expression);

            virtual void* accept(Visitor<void*>* visitor);
    };
} 
