#include "./../../include/Interpreter/LoxInstance.h"

LoxInstance::LoxInstance(LoxClass* klass)
{
    this->klass = klass;
}