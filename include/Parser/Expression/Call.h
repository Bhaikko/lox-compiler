#pragma once

#include <vector>

#include "./../../Scanner/Token.h"
#include "./Expr.h"

namespace Expr
{
    class Call: public Expr 
    {
        public:
            Expr* callee;
            Token* paren;   // Required for throwing error
            std::vector<Expr*>* arguments;

        public:
            Call(Expr* callee, Token* paren, std::vector<Expr*>* arguments);

            std::string* accept(Visitor<std::string*>* visitor);

    };
}
