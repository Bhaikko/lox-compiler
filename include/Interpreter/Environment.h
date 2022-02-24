#pragma once

#include <string>
#include <unordered_map>

#include "./../Scanner/Token.h"
#include "./RuntimeError.h"

class Environment
{
    private:
        std::unordered_map<std::string, std::string*>* values;

    public:
        // Reference to Environment of parent block
        Environment* enclosing;

    public:
        Environment();
        Environment(Environment* enclosing);

    public:
        /**
         * @brief used to define a variable when Var keyword is used
         * 
         * @param name 
         * @param value 
         */
        void define(std::string* name, std::string* value);

        /**
         * @brief Used to assign new value to identifier 
         * once it is already defined in memory.
         * Assignment is not allowed to create new variable
         * 
         * @param name 
         * @param value 
         */
        void assign(Token* name, std::string* value);
        std::string* get(Token* name);
};