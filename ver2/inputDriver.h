#ifndef JSON_INPUTDRIVER_H
#define JSON_INPUTDRIVER_H

#include <string>
#include <iostream>

class InputDriver{

public:

    std::string inputData;
    size_t pos;

    InputDriver(std::string inputStr);
    InputDriver(){}

    char getChar();
    char writeBack();

    friend class Lexer;
    friend class parserFunctionality;

    
};

#endif // JSON_INPUTDRIVER_H