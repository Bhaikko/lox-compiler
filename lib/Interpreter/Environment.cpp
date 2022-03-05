#include "./../../include/Interpreter/Environment.h"

Environment::Environment()
{
    this->values = new std::unordered_map<std::string, void*>();
    this->enclosing = nullptr;
}

Environment::Environment(Environment* enclosing)
{
    this->values = new std::unordered_map<std::string, void*>();
    this->enclosing = enclosing;
}

void Environment::define(std::string* name, void* value)
{
    // Not checking existing variable for redefinition
    (*values)[*name] = value;
}

void* Environment::get(Token* name)
{
    if (values->find(*(name->lexeme)) != values->end()) {
        return values->at(*(name->lexeme));
    }

    if (enclosing != nullptr) {
        // Recursively searches in enclosing environment
        return enclosing->get(name);
    }

    throw new RuntimeError(name, "Undefined variable '" + *(name->lexeme) + "'.");
}

void Environment::assign(Token* name, void* value)
{
    if (values->find(*(name->lexeme)) != values->end()) {
        (*values)[*(name->lexeme)] = value;
        return;
    }

    if (enclosing != nullptr) {
        // Recursively look for name to assign too
        enclosing->assign(name, value);
        return;
    }

    throw new RuntimeError(name, "Undefined variable '" + *name->lexeme + "'.");
}


void* Environment::getAt(int distance, std::string name)
{
    // No need to check for variable existence
    // Since the resolver already found it and 
    // declared it in locals
    return ancestor(distance)->values->at(name);
}

Environment* Environment::ancestor(int distance)
{
    Environment* environment = this;
    for (int i = 0; i < distance; i++) {
        environment = environment->enclosing;
    }

    return environment;
}
