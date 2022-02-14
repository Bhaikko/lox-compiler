#include "./../../include/Parser/Grouping.h"      
                                                        
Grouping::Grouping(Expr* expression)               
{                                                      
    this->expression = expression;                     
};                                                     

// std::string Grouping::accept(Visitor<std::string>* visitor)
std::string Grouping::accept(Visitor* visitor)
{
    return visitor->visitGroupingExpr(this);
}
