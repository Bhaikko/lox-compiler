#pragma once                          
                                        
#include "./../../Scanner/Token.h"       
#include "./Expr.h"                   

namespace Expr {                                        
    class Grouping : public Expr                  
    {                                      
        public:                            
            Expr* expression;  
                                
        public:                             
            Grouping(Expr* expression);   

            virtual std::string* accept(Visitor<std::string*>* visitor) override;
    };                                     
}