#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include "./../Scanner/Token.h"
#include "./RuntimeError.h"

#include "./../Native/Clock.h"

class Environment
{
    private:
        std::unordered_map<std::string, void*>* values;

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
        void define(std::string* name, void* value);

        /**
         * @brief Used to assign new value to identifier 
         * once it is already defined in memory.
         * Assignment is not allowed to create new variable
         * 
         * @param name 
         * @param value 
         */
        void assign(Token* name, void* value);

        /**
         * @brief Searches dynamically at runtime for the variable definition
         * 
         * @param name 
         * @return void* 
         */
        void* get(Token* name);

    public:
        /**
         * @brief Searches the variable based on distance obtained static analyis in resolver
         * 
         * @param distance 
         * @param name 
         * @return void* 
         */
        void* getAt(int distance, std::string name);
        void assignAt(int distance, Token* name, void* value);

    private:    
        Environment* ancestor(int distance);
};