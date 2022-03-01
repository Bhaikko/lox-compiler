#pragma once

#include <vector>
#include <string>

class Interpreter;

class LoxCallable
{
    public:
        LoxCallable();
        virtual unsigned int arity();
        virtual std::string* call(Interpreter* interpreter, std::vector<std::string*>* arguments);
        virtual std::string* toString();
};