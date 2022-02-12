## This file contains grammer structure for lox language

```
    expression  ->  literal
                |   unary
                |   binary
                |   grouping ;
    
    literal     ->  NUMBER | STRING | "true" | "false" | "nil" ;
    grouping    ->  "(" expression ")";
    unary       ->  ( "-" | "!" ) expression ;
    binary      ->  expression operator expresion ;
    operator    ->  "==" | "!=" | "<" | "<=" | ">" | ">=" 
                |   "+" | "-" | "*" | "/" ; 
```