#pragma once

#include "./../../Scanner/Token.h"
#include "./Expr.h"

namespace Expr {
    class Set: public Expr 
    {
        public:
            Expr* object;
            Token* name;
            Expr* value;

        public:
            Set(Expr* object, Token* name, Expr* value);

        public:
            std::string* accept(Visitor<std::string*>* visitor);
    };
}