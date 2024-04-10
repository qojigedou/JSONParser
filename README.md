### JSON Parser

## Structure:

1. Input Driver
2. Lexer
3. Parser

## Parser Logic:

```
 <Json> ::= <Object>
          | <Array>

 <Object> ::= '{' [<Members>] '}'

 <Members> ::= <Pair> [',' <Members>]

 <Pair> ::= String ':' <Value>

 <Array> ::= '[' [<Elements>] ']'

 <Elements> ::= <Value> [',' <Elements>]

 <Value> ::= String
           | Number
           | <Object>
           | <Array>
           | true
           | false
           | null
```
