### JSON Parser

A JSON parser is a software component or module that is used to interpret and analyze JSON data. JSON is a lightweight data-interchange format that is easy to read and write and for machines to parse and generate. JSON parsers are commonly found in programming languages and frameworks, and they serve to parse JSON data into a format that can be easily manipulated and used within a given programming environment.

Parsing is essentially the process of recognizing the shape of a particular input string and understanding some concept.

## Structure:

1. Input Driver - it is responsible for handling an input
2. Lexer - it is used to handle the string in the best way for the system.
   The main logic is in state machine. A state machine is a graph composed of vertices connected by edges. The graph has a single starting vertex and one or more middle or final tokens. Landing on a final vertex means that a new token is created. Edges allow input characters to traverse the graph by assigning a letter label to each edge.

```
const uint8_t Lexer::stateMachine[19][24];
```

where there is a list of states/vertices of the state machine and list of transitions/edges of the state machine

3. Parser is responsible for syntactical analysis, which involves examining the structure of a JSON document to ensure it conforms to the JSON format specification. It includes actual parsing with the logic provided below, syntax checking and error handling.

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

### Members of JSON logic

```
    OBJECT,
    ARRAY,
    BOOLEAN,
    NIL,
    INTEGER,
    FLOAT,
    STRING
```

### Tokens

```
    LBRA, - "["
    RBRA, - "]"
    LSQBRA, - "{"
    RSQBRA, - "}"
    COMMA,  - ","
    NUMBER, - number value
    COLON, - ":"
    STRING, -string value
    ERROR, - error
    BOOL_VALUE, - boolean value (True/False)
    NULL_VALUE, - null
    EOI - end of inputs

```
