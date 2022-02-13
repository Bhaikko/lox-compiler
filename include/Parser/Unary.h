#pragma once                          
                                        
#include "./../Scanner/Token.h"       
#include "./Expr.h"                   
                                        
class Unary : public Expr                  
{                                      
    private:                            
        Token* operator_;  
		Expr* right;  
		                    
    public:                             
        Unary(Token* operator_, Expr* right);   
};                                     
