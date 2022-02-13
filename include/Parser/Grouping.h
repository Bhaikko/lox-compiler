#pragma once                          
                                        
#include "./../Scanner/Token.h"       
#include "./Expr.h"                   
                                        
class Grouping : public Expr                  
{                                      
    private:                            
        Expr* expression;  
		                    
    public:                             
        Grouping(Expr* expression);   
};                                     
