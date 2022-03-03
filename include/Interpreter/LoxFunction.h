#pragma once

#include "./LoxCallable.h"
#include "./Return.h"
#include "./../Parser/Stmt/StmtHeaders.h"

/**
 * @brief Runtime representation of Compiled time syntax node of Function
 * 
 */
class LoxFunction: public LoxCallable
{
    public:
        Stmt::Function* declaration;
        Environment* closure;

    public:
        LoxFunction(Stmt::Function* declaration, Environment* closure);
        virtual unsigned int arity() override;
        virtual std::string* call(Interpreter* interpreter, std::vector<std::string*>* arguments) override;

        friend std::ostream& operator<<(std::ostream& os, const LoxFunction& t);

};