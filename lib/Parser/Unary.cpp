#include "./../../include/Parser/Unary.h"      
                                                        
Unary::Unary(Token* operator_, Expr* right)                
{                                                      
    this->operator_ = operator_;
	this->right = right;
	                                        
};                                                     
