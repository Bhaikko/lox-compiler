#pragma once                          
                                        
#include "./../Scanner/Token.h"       
#include "./Expr.h"                   
                                        
class Literal                        
{                                      
    private:                            
        std::string* value;  
		                    
    public:                             
        Literal(std::string* value);   
};                                     
