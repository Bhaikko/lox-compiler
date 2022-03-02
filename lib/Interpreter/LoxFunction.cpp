#include "./../../include/Interpreter/LoxFunction.h"

LoxFunction::LoxFunction(Stmt::Function* declaration)
{
    this->declaration = declaration;
}

unsigned int LoxFunction::arity()
{
    return declaration->params->size();
}

std::string* LoxFunction::call(Interpreter* interpreter, std::vector<std::string*>* arguments)
{
    // Creating local scope for Function call
    Environment* environment = new Environment(interpreter->globals);

    // Binding each arguement pair in Environment
    for (unsigned int i = 0; i < declaration->params->size(); i++) {
        environment->define(
            declaration->params->at(i)->lexeme,
            static_cast<void*>(arguments->at(i))
        );
    }

    try {
        interpreter->executeBlock(declaration->body, environment);
    } catch (Runtime::Return* returnValue) {
        // Used to return from callstack 
        return static_cast<std::string*>(returnValue->value);
    }

    return nullptr;
}

std::ostream& operator<<(std::ostream& os, const LoxFunction& t) {
    os << "<fn " + *t.declaration->name->lexeme + ">";
    return os;
}