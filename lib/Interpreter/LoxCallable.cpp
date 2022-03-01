#include "./../../include/Interpreter/LoxCallable.h"

LoxCallable::LoxCallable()
{
    
}

unsigned int LoxCallable::arity()
{
    return 0;
}

std::string* LoxCallable::call(Interpreter* interpreter, std::vector<std::string*>* arguments)
{
    return nullptr;
}

std::string* LoxCallable::toString()
{
    return nullptr;
}