#pragma once

#include <vector>
#include <string>

class Interpreter;

class LoxCallable
{
    public:
        virtual std::string* call(Interpreter* interpreter, std::vector<std::string*>* arguments);
};