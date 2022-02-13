#include "./../../include/Parser/AstPrinter.h"

std::string AstPrinter::print(Expr* expr)
{
    return expr->accept(this);
}