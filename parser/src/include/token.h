#ifndef JSON_TOKEN_H
#define JSON_TOKEN_H

#include <string>

namespace json {

class Token {
    friend class Lexer;
    friend class Parser;

private:
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

}; // namespace json

#endif // JSON_TOKEN_H