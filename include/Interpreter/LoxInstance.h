#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include "./../Scanner/Token.h"
#include "./RuntimeError.h"

class LoxClass;

class LoxInstance
{
    public:
        LoxClass* klass;

    public:
        std::unordered_map<std::string, void*>* fields;

    public:
        LoxInstance(LoxClass* klass);

    public:
        void* get(Token* name);
        void set(Token* name, void* value);
};