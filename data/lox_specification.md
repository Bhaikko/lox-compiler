## This file contains grammer structure for lox language and language related notes

### Expression Grammar
```
    program     ->  declaration* EOF ;
    declaration ->  funDecl | varDecl | statement;
    funDecl     ->  "fun" function;
    varDecl     ->  "var" IDENTIFIER ( "=" expression )? ";" ;
    statement   ->  exprStmt | printStmt | block | ifStmt |
                    whileStmt | forStmt | returnStmt;

    function    ->  IDENTIFIER "(" parameters? ")" block ;
    exprStmt    ->  expression ";" ;
    printStmt   ->  "print" expression ";" ;
    block       ->  "{" declaration* "}" ;
    ifStmt      ->  "if" "(" expression ")" statement
                    ( "else" statement )? ;
    whileStmt   ->  "while" "(" expression ")" statement;
    forStmt     ->  "for" "(" (varDevl | exprStmt | ";" )
                    expression? ";" 
                    expression? ")" statement ;
    returnStmt  ->  "return" expression? ";" ;

    expression  ->  assignment;
    assignment  ->  IDENTIFIER "=" assignment | logic_or ;
    logic_or    ->  logic_and ( "or" logic_and )* ;
    logic_and   ->  equality ( "and" equality )* ;
    equality    ->  comparison ( ( "!=" | "==" ) comparison )* ;
    comparison  ->  term ( ( ">" | ">=" | "<" | "<=" ) term )* ; 
    term        ->  factor ( ( "-" | "+" ) factor )* ;
    factor      ->  unary ( ( "/" | "*" ) unary )* ;
    unary       ->  ("!" | "-" ) unary
                    |   call;
    call        ->  primary ( "(" arguments? ")" )* ;
    parameters  ->  IDENTIFIER ( "," IDENTIFIER )* ;
    arguments   ->  expression ( "," expression )* ;
    primary     ->  NUMBER | STRING | "true" | "false" | "nil"
                    |   "(" expression ")" | IDENTIFIER ;
```
_Lower Non terminals have higher precedence_

### Non boolean values and Bang operator
```
Lox follows Ruby's rule: false and nil are falsey.
Everything else is true
```

### Logical Expression
```
Short circuiting implemented for Boolean expressions
And has higher precedence than Or

```