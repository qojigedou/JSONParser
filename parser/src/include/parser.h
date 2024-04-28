#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include "inputDriver.h"
#include "token.h"
#include "lexer.h"
#include "member.h"
#include "container.h"

#include <map>
#include <stdexcept>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stack>

namespace json
{

    class Parser
    {
        Lexer lexer;
        Token token;
        std::stack<std::string> keys;
        std::stack<json::Container *> containers;
        json::Container *root = nullptr;

        bool accept(Token::Type type);

        void parseJSON();
        void parseObject();
        void parseArray();
        void parseMembers();
        void parsePair();
        void parseElements();
        void parseValue();
        bool stringToBool(std::string stringValue);
        void printMap(Member *top);

    public:
        void parse();
        static std::string readJsonFromFile(const std::string &filename);

        void printMap();

        Parser(){};
        Parser(const std::string &input);
        ~Parser(){};
    };

}; // namespace json

#endif // JSON_PARSER_H
