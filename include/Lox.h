#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "./Scanner/Scanner.h"
#include "./Parser/Parser.h"
#include "./Parser/AstPrinter.h"
#include "./Interpreter/RuntimeError.h"

class Lox
{
    public:
        static bool hadError;
        static bool hadRuntimeError;

    private:
        static void report(int line, std::string where, std::string message);

    public:
        // Reports an Error for a given Token
        static void error(Token* token, std::string message);
        static void runtimeError(RuntimeError error);
        
        // Reports an Error for a given Character 
        static void error(int line, std::string message);
        static void run(std::string* srcCode);
        static void runFile(char* filepath);
        static void runPrompt();

};

