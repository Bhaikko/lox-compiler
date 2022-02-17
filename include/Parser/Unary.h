#pragma once                          
                                        
#include "./../Scanner/Token.h"       
#include "./Expr.h"                   
                                        
class Unary : public Expr                  
{                                      
    public:                            
        Token* operator_;  
		Expr* right;  
		                    
    public:                             
        Unary(Token* operator_, Expr* right);   

        virtual std::string* accept(Visitor<std::string*>* visitor) override;
};                                     
