## This file contains grammer structure for lox language

_The previous grammar was ambigous_

### Expression Grammar
```
    expression  ->  equality;
    equality    ->  comparison ( ( "!=" | "==" ) comparison )* ;
    comparison  ->  term ( ( ">" | ">=" | "<" | "<=" ) term )* ; 
    term        ->  factor ( ( "-" | "+" ) factor )* ;
    factor      ->  unary ( ( "/" | "*" ) unary )* ;
    unary       ->  ("!" | "-" ) unary
                |   primary;
    primary     ->  NUMBER | STRING | "true" | "false" | "nil"
                |   "(" expression ")" ;
```
_Lower Non terminals have higher precedence_