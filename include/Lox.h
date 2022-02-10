#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "./Scanner.h"

class Lox
{
    public:
        static bool hadError;

    private:
        static void report(int line, std::string where, std::string message);

    public:
        
        static void error(int line, std::string message);
        static void run(std::string* srcCode);
        static void runFile(char* filepath);
        static void runPrompt();

};

// bool Lox::hadError = false;

