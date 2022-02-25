#pragma once

#include "./../../Scanner/Token.h"
#include "./Expr.h"

namespace Expr {
    class Logical: public Expr 
    {
        public: 
            Expr* left;
            Token* operator_;
            Expr* right;

        public:
            Logical(Expr* left, Token* operator_, Expr* right);

            virtual std::string* accept(Visitor<std::string*>* visitor) override;
    };
}