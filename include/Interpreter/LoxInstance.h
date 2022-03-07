#pragma once

#include <unordered_map>
#include <string>

#include "./../Scanner/Token.h"
#include "./RuntimeError.h"

class LoxClass;

class LoxInstance
{
    public:
        LoxClass* klass;

    private:
        std::unordered_map<std::string, void*>* fields;

    public:
        LoxInstance(LoxClass* klass);

    public:
        void* get(Token* name);
};