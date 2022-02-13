#pragma once                          
                                        
#include "./../Scanner/Token.h"       
#include "./Expr.h"                   
                                        
class Unary                        
{                                      
    private:                            
        Token* operator,;  
		Expr* right;  
		                    
    public:                             
        Unary(Token* operator,, Expr* right);   
};                                     
