#pragma once                          
                                        
#include "./../Scanner/Token.h"       
#include "./Expr.h"                   
                                        
class Grouping                        
{                                      
    private:                            
        Expr* expression;  
		Token* operator_;  
		                    
    public:                             
        Grouping(Expr* expression, Token* operator_);   
};                                     
                                        
                                        
