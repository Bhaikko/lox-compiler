#pragma once

#include "./../../Scanner/Token.h"
#include "./Expr.h"

namespace Expr
{
    class Variable : public Expr                  
    {                                      
        public:                            
            Token* name;  
                                
        public:                             
            Variable(Token* name);   

            virtual std::string* accept(Visitor<std::string*>* visitor) override;
    }; 
} 
