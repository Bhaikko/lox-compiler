#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "./../include/Lox.h"

#include "./../include/Parser/AstPrinter.h"

int main(int argc, char** argv)
{
    // if (argc > 2) {
    //     std::cout << "Usage: jlox [script]" << std::endl;
    //     exit(1);
    // } else if (argc == 2) {
    //     // If File path is provided
    //     Lox::runFile(argv[1]);
    // } else {
    //     // Running an Interactive Console - REPL
    //     Lox::runPrompt();
    // }

    Binary* expr = new Binary(
        new Unary(
            new Token(
                TokenType::MINUS, 
                new std::string("-"),
                nullptr,
                1
            ),
            new Literal(new std::string("123"))
        ),
        new Token(
            TokenType::STAR, 
            new std::string("*"),
            nullptr,
            1
        ),
        new Grouping(new Literal(new std::string("45.67")))
    );

    AstPrinter* printer = new AstPrinter();
    // printer->print(expr);

    return 0;
}