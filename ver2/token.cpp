#include "token.h"

void Token::popChar(){
    lexeme.pop_back();
}

void Token::pushChar(char c){
    lexeme.push_back(c);
}