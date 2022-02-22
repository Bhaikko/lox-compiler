#include "./../../../include/Parser/Expression/Variable.h"      
                                                        
Expr::Variable::Variable(Token* name)               
{                                                      
    this->name = name;                     
};                                                     

std::string* Expr::Variable::accept(Visitor<std::string*>* visitor)
{
    return visitor->visitVariableExpr(this);
}
