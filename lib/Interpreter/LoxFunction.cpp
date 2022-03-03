#include "./../../include/Interpreter/LoxFunction.h"

LoxFunction::LoxFunction(Stmt::Function* declaration, Environment* closure)
{
    this->declaration = declaration;
    this->closure = closure;
}

unsigned int LoxFunction::arity()
{
    return declaration->params->size();
}

std::string* LoxFunction::call(Interpreter* interpreter, std::vector<std::string*>* arguments)
{
    // Creating local scope for Function call 
    // with closure environment as it parent
    Environment* environment = new Environment(closure);

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