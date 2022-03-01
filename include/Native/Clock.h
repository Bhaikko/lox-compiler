#pragma once

#include <ctime>
#include <chrono>

#include "./../Interpreter/LoxCallable.h"

class Clock: public LoxCallable
{
    public:
        virtual unsigned int arity() override;
        virtual std::string* call(Interpreter* interpreter, std::vector<std::string*>* arguements);
};

/*
    if we want to add other native functions- eg, reading input from user, etc
    we could add them each as their own anonymous class that implements LoxCallable
*/