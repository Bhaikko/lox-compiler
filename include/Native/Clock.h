#pragma once

#include <ctime>
#include <chrono>

#include "./../Interpreter/LoxCallable.h"

class Clock: public LoxCallable
{
    public:
        virtual unsigned int arity() override;
        virtual std::string* call(Interpreter* interpreter, std::vector<std::string*>* arguements) override;

        friend std::ostream& operator<<(std::ostream& os, const Clock& t);
};

/*
    if we want to add other native functions- eg, reading input from user, etc
    we could add them each as their own anonymous class that implements LoxCallable
*/