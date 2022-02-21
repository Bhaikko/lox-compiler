#include "./../../../include/Parser/Expression/Grouping.h"      
                                                        
Expr::Grouping::Grouping(Expr* expression)               
{                                                      
    this->expression = expression;                     
};                                                     

std::string* Expr::Grouping::accept(Visitor<std::string*>* visitor)
{
    return visitor->visitGroupingExpr(this);
}
