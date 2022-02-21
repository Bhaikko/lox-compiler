#include "./../../../include/Parser/Expression/Literal.h"      
                                                        
Expr::Literal::Literal(std::string* value)               
{                                                      
    this->value = value;                                  
};                                                     

std::string* Expr::Literal::accept(Visitor<std::string*>* visitor)
{
    return visitor->visitLiteralExpr(this);
}
