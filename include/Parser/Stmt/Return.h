#pragma once

#include "./../../Scanner/Token.h"
#include "./Stmt.h"

namespace Stmt {
    class Return: public Stmt 
    {
        public:
            // keyword to report errors
            Token* keyword;
            Expr::Expr* value;

        public:
            Return(Token* keyword, Expr::Expr* value);
            virtual void* accept(Visitor<void*>* visitor) override;
    };
}