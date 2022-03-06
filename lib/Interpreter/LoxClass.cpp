#include "./../../include/Interpreter/LoxClass.h"

LoxClass::LoxClass(std::string* name)
{
    this->name = name;
}

unsigned int LoxClass::arity()
{
    return 0;
}

std::string* LoxClass::call(Interpreter* interpreter, std::vector<std::string*>* arguments)
{
    LoxInstance* instance = new LoxInstance(this);
    
    // Need to fix the call method because of this
    return static_cast<std::string*>(
        static_cast<void*>(instance)
    );
}
