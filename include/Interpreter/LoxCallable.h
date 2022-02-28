#pragma once

#include <vector>
#include <string>

class Interpreter;

class LoxCallable
{
    public:
        LoxCallable();
        virtual int arity();
        virtual std::string* call(Interpreter* interpreter, std::vector<std::string*>* arguments);
};