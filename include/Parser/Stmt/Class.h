#pragma once

#include <vector>

#include "./../../Scanner/Token.h"
#include "./Stmt.h"
#include "./Function.h"

namespace Stmt {
    class Class: public Stmt 
    {
        public:
            // Stores class name and methods inside the body
            Token* name;
            std::vector<Function*>* methods;

        public:
            Class(Token* name, std::vector<Function*>* methods);
            virtual void* accept(Visitor<void*>* visitor);

    };
}