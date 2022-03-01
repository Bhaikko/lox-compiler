#pragma once

#include "./LoxCallable.h"
#include "./../Parser/Stmt/StmtHeaders.h"

class LoxFunction: public LoxCallable
{
    public:
        Stmt::Function* declaration;

    public:
        LoxFunction(Stmt::Function* declaration);
        virtual unsigned int arity() override;
        virtual std::string* call(Interpreter* interpreter, std::vector<std::string*>* arguments) override;

        friend std::ostream& operator<<(std::ostream& os, const Token& t);

};