#ifndef JSON_INPUTDRIVER_H
#define JSON_INPUTDRIVER_H

#include <string>
#include <iostream>

namespace json
{

    class InputDriver
    {
        friend class Lexer;
        friend class Parser;

    private:
        std::string inputData;
        size_t pos;

        InputDriver(std::string inputStr);
        InputDriver() {}
        ~InputDriver(){};

        char getChar();
        char writeBack();
    };

}; // namespace json

#endif // JSON_INPUTDRIVER_H