#pragma once

#include "./../../Scanner/Token.h"
#include "./Stmt.h"

namespace Stmt
{
    class Var: public Stmt 
    {
        public:
            Token* name;
            Expr::Expr* initializer;

        public:
            Var(Token* name, Expr::Expr* initializer);

            virtual void* accept(Visitor<void*>* visitor) override; 
    };  
} 
