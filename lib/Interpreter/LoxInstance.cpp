#include "./../../include/Interpreter/LoxInstance.h"

LoxInstance::LoxInstance(LoxClass* klass)
{
    this->klass = klass;
    this->fields = new std::unordered_map<std::string, void*>();
}

void* LoxInstance::get(Token* name)
{
    if (fields->find(*name->lexeme) != fields->end()) {
        return fields->at(*name->lexeme);
    }

    // If the property does not exist then a runtime error is throw
    throw new RuntimeError(name,
        "Undefined property '" + *name->lexeme + "'."
    );
}
