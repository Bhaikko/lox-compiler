#pragma once

#include <string>

#include "./LoxCallable.h"
#include "./LoxInstance.h"

/**
 * @brief Runtime Representation of Class in Lox
 * Inherits from LoxCallable because the instancing of object is by
 * calling ClassName as Function
 */
class LoxClass: public LoxCallable
{
    public:
        std::string* name;

    public:
        LoxClass(std::string* name);

    public:
        /**
         * @brief Returns number of arguements passed to constructor
         * 
         * @return unsigned int 
         */
        virtual unsigned int arity() override;
        virtual std::string* call(Interpreter* interpreter, std::vector<std::string*>* arguments) override;
};