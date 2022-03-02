#include "./../../include/Interpreter/Return.h"

Interpreter::Return::Return(void* value) : std::runtime_error("")
{
    this->value = value;
}