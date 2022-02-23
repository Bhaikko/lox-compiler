#pragma once

#include "./../../Scanner/Token.h"
#include "./Expr.h"

namespace Expr {
    class Assign: public Expr 
    {
        public:
            Token* name;
            Expr* value;

        public:
            Assign(Token* name, Expr* value);

            virtual std::string* accept(Visitor<std::string*>* visitor) override;
    };
}