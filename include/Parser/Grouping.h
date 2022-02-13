#pragma once                          
                                        
#include "./../Scanner/Token.h"       
#include "./Expr.h"                   
                                        
class Grouping                        
{                                      
    private:                            
        Expr* expression;  
		                    
    public:                             
        Grouping(Expr* expression);   
};                                     
