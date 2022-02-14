#pragma once

#include "./../Scanner/Token.h"
#include "./Expr.h"

/**
 * @brief Derived class of Expr. 
 * Will define grammar production rules like this by indiviually mentioning the
 * Non terminals and Terminals
 * 
 * Refer to /data/lox_grammar.md for Grammar Speicifications
 */
class Binary : public Expr
{   // The base classes will have subclasses nested inside of it
    public:
        Expr* left;
        Token* operator_;    // operator is a keyword in Cpp
        Expr* right;

    public:
        Binary(Expr* left, Token* operator_, Expr* right);

        virtual std::string accept(Visitor<std::string>* visitor) override;
};

// The process of generating Subclasses such as above is Automated
// tools/GenerateAst.cpp is used to Generate such Sub classes
