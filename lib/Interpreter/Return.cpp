#include "./../../include/Interpreter/Return.h"

Runtime::Return::Return(void* value) : std::runtime_error("")
{
    this->value = value;
}