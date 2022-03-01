#pragma once

#include "./../../Scanner/Scanner.h"
#include "./Stmt.h"

namespace Stmt {
    class Function: public Stmt 
    {
        public:
            Token* name;
            std::vector<Token*>* params;
            std::vector<Stmt*>* body;

        public:
            Function(Token* name, std::vector<Token*>* params, std::vector<Stmt*>* body);
            void* accept(Visitor<void*>* visitor);
        
    };
}