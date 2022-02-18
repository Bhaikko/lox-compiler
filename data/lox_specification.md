## This file contains grammer structure for lox language and language related notes

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

### Non boolean values and Bang operator
Lox follows Ruby's rule: false and nil are falsey. <br/>
Everything else is true