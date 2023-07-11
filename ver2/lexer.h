#ifndef JSON_LEXER_H
#define JSON_LEXER_H

#include "inputDriver.h"
#include "token.h"

#include <string>

class Lexer {
public:
    Lexer(const InputDriver& inputData);
    Token getToken();
    Lexer();

private:
    InputDriver inputData;
    uint8_t state;
    static const uint8_t stateMachine[19][24];
    static const uint8_t firstFinalState;
    static const uint8_t firstWritebackState;
    static const Token::Type finalStateTypes[];
    
    size_t getCharacterClass(const char c);
    bool isFinalState(uint8_t state);
    bool isWritebackState(uint8_t state);
    Token::Type getFinalStateType(uint8_t state);
};

#endif // JSON_LEXER_H