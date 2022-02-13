#pragma once                          
                                        
#include "./../Scanner/Token.h"       
#include "./Expr.h"                   
                                        
class Literal : public Expr                       
{                                      
    private:                            
        std::string* value;  
		                    
    public:                             
        Literal(std::string* value);   
};                                     
