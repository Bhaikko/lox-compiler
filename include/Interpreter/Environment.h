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
        Environment();

    public:
        void define(std::string* name, std::string* value);
        std::string* get(Token* name);
};