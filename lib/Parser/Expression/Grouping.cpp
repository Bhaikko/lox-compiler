#include "./../../../include/Parser/Expression/Grouping.h"      
                                                        
Grouping::Grouping(Expr* expression)               
{                                                      
    this->expression = expression;                     
};                                                     

std::string* Grouping::accept(Visitor<std::string*>* visitor)
{
    return visitor->visitGroupingExpr(this);
}
