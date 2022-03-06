#pragma once

class LoxClass;

class LoxInstance
{
    public:
        LoxClass* klass;

    public:
        LoxInstance(LoxClass* klass);
};