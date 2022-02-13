#pragma once

#include <string>

#include "./Expr.h"

class AstPrinter : public Visitor<std::string>
{
    public:
        std::string print(Expr* expr);
};

