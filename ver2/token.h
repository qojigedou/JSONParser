#ifndef JSON_TOKEN_H
#define JSON_TOKEN_H

#include <string>

class Token {
    friend class Lexer;
    friend class Parser;

public:
    typedef enum {
        LBRA,
        RBRA,
        LSQBRA,
        RSQBRA,
        COMMA,
        NUMBER,
        COLON,
        STRING,
        ERROR,
        BOOL_VALUE,
        NULL_VALUE,
        EOI
    } Type;

    Type type;
    std::string lexeme{""};

    void pushChar(char c);
    void popChar();
};

#endif // JSON_TOKEN_H