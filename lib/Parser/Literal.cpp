#include "./../../include/Parser/Literal.h"      
                                                        
Literal::Literal(std::string* value)               
{                                                      
    this->value = value;                                  
};                                                     

std::string Literal::accept(Visitor<std::string>* visitor)
{
    return visitor->visitLiteralExpr(this);
}
