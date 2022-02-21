#pragma once                          
                                        
#include "./../../Scanner/Token.h"       
#include "./Expr.h"                   

namespace Expr {    
    class Literal : public Expr                       
    {                                      
        public:                            
            std::string* value;  
                                
        public:                             
            Literal(std::string* value);   
            
            virtual std::string* accept(Visitor<std::string*>* visitor) override;
    };                                     
}