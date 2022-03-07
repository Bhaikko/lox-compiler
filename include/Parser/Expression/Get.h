#pragma once

#include "./../../Scanner/Token.h"
#include "./Expr.h"

namespace Expr {
    /**
     * @brief Foe property accesses of class instances
     * 
     */
    class Get: public Expr 
    {
        public:
            Expr* object;
            Token* name;

        public:
            Get(Expr* object, Token* name);

        public:
            virtual std::string* accept(Visitor<std::string*>* visitor) override;
    };
}