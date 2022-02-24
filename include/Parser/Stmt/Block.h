#pragma once

#include <vector>

#include "./Stmt.h"

namespace Stmt {
    class Block: public Stmt 
    {
        public:
            // Contains references to all statements inside the block
            std::vector<Stmt*>* statements;

        public:
            Block();
            Block(std::vector<Stmt*>* statements);

            virtual void* accept(Visitor<void*>* visitor) override;
    };
}