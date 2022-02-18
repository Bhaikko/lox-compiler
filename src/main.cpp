#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "./../include/Lox.h"

#include "./../include/Parser/AstPrinter.h"

int main(int argc, char** argv)
{
    if (argc > 2) {
        std::cout << "Usage: jlox [script]" << std::endl;
        exit(1);
    } else if (argc == 2) {
        // If File path is provided
        Lox::runFile(argv[1]);
    } else {
        // Running an Interactive Console - REPL
        Lox::runPrompt();
    }

    return 0;
}