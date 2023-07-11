#include "lexer.h"


Lexer::Lexer(const InputDriver& inputData) : inputData(inputData) {}
Lexer::Lexer(){
    state = 0;
}

// this table may seem complicated, because it really is (from JSON grammar)
const uint8_t Lexer::stateMachine[19][24] = {
    {31, 19, 20, 21, 22, 23, 3, 2, 31, 1, 24, 0, 4, 31, 31, 9, 12, 15, 31, 31, 31, 31, 31, 31},
    {31, 31, 31, 31, 31, 31, 3, 2, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31},
    {29, 29, 29, 29, 29, 29, 29, 29, 6, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29},
    {29, 29, 29, 29, 29, 29, 3, 3, 6, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29},
    {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 25, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
    {31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 8, 8, 8, 8, 8, 8, 31, 31, 8, 31, 31, 31},
    {31, 31, 31, 31, 31, 31, 7, 7, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31},
    {30, 30, 30, 30, 30, 30, 7, 7, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
    {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 25, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
    {31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 10, 31, 31, 31, 31, 31},
    {31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 11, 31, 31, 31, 31},
    {31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 26, 31, 31, 31, 31},
    {31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 13, 31, 31, 31},
    {31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 14, 31, 31, 31, 31, 31},
    {31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 27, 31, 31},
    {31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 16, 31},
    {31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 17, 31, 31, 31, 31},
    {31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 18},
    {31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 28, 31, 31}
};

const uint8_t Lexer::firstFinalState = 19;
const uint8_t Lexer::firstWritebackState = 29;
const Token::Type Lexer::finalStateTypes[] = { Token::LBRA, Token::RBRA, Token::LSQBRA, Token::RSQBRA, Token::COMMA, Token::COLON, Token::STRING, Token::NULL_VALUE, Token::BOOL_VALUE, Token::BOOL_VALUE, Token::NUMBER, Token::NUMBER, Token::ERROR};

size_t Lexer::getCharacterClass(const char c){
    if(c == '{') return 1;
    if(c == '}') return 2;
    if(c == '[') return 3;
    if(c == ']') return 4;
    if(c == ',') return 5;
    if(c > '0' &&  c <= '9') return 6;
    if(c == '0') return 7;
    if(c == '.') return 8;
    if(c == '-') return 9;
    if(c == ':') return 10;
    if(c == ' ' || c == '\n' || c == '\r' || c == '\t') return 11;
    if(c == '"') return 12;
    if(c == '\\') return 13;
    if(c == '/' || c == 'b') return 14;
    if(c == 'n') return 15;
    if(c == 't') return 16;
    if(c == 'f') return 17;
    if(c == 'u') return 18;
    if(c == 'l') return 19;
    if(c == 'r') return 20;
    if(c == 'e') return 21;
    if(c == 'a') return 22;
    if(c == 's') return 23;
    return 0;
}

bool Lexer::isFinalState(uint8_t state) {
    return (state >= Lexer::firstFinalState);
}

bool Lexer::isWritebackState(uint8_t) {
    return (state >= Lexer::firstWritebackState);
}

Token::Type Lexer::getFinalStateType(uint8_t state) {
    return finalStateTypes[state - Lexer::firstFinalState];
}

Token Lexer::getToken() {
    Token token;
    this->state = 0;
    char c = '\0';
    while((c = inputData.getChar()) != '\0') {
        uint8_t nextState = Lexer::stateMachine[this->state][getCharacterClass(c)];
        this->state = nextState;
        token.pushChar(c);

        if(isFinalState(this->state)) {
            token.type = getFinalStateType(this->state);

            if(isWritebackState(this->state)) {
                inputData.writeBack();
                token.popChar();
            }

            return token;
        }
    }

    token.type = Token::EOI;
    return token;
}