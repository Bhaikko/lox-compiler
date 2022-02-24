#include "./../../include/Interpreter/Environment.h"

Environment::Environment()
{
    this->values = new std::unordered_map<std::string, std::string*>();
    this->enclosing = nullptr;
}

Environment::Environment(Environment* enclosing)
{
    this->values = new std::unordered_map<std::string, std::string*>();
    this->enclosing = enclosing;
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

    if (enclosing != nullptr) {
        // Recursively searches in enclosing environment
        return enclosing->get(name);
    }

    throw new RuntimeError(name, "Undefined variable '" + *(name->lexeme) + "'.");
}

void Environment::assign(Token* name, std::string* value)
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