#pragma once

#include "./Stmt.h"

namespace Stmt
{
    class Expression: public Stmt
    {
        public:
            Expr* expression;

        public:
            Expression(Expr* expression);

            virtual void* accept(Visitor<void*>* visitor);
    };
} 
