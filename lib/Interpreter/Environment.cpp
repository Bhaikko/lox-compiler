#include "./../../include/Interpreter/Environment.h"

Environment::Environment()
{
    this->values = new std::unordered_map<std::string, std::string*>();
}

void Environment::define(std::string* name, std::string* value)
{
    // Not checking existing variable for redefinition
    (*values)[*name] = value;
}

std::string* Environment::get(Token* name)
{
    if (values->find(*(name->lexeme)) != values->end()) {
        return values->at(*(name->lexeme));
    }

    throw new RuntimeError(name, "Undefined variable '" + *(name->lexeme) + "'.");
}

