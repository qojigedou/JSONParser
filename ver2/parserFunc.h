#include "inputDriver.h"
#include "token.h"
#include "lexer.h"
#include <map>
#include <stdexcept>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stack>


class Parser {
    typedef enum {
        OBJECT,
        ARRAY,
        BOOLEAN,
        NIL,
        INTEGER,
        FLOAT,
        STRING
    } MemberType;

    struct JSONMember {
        MemberType type;
        void* value;
    };

    Lexer lexer;
    Token token;
    std::stack<std::string> keys;
    std::stack<JSONMember*> members;
    JSONMember root;
    std::vector<JSONMember*> arrMember;

    void parseJSON();
    void parseObject();
    void parseArray();
    void parseMember();
    void parsePair();
    void parseElements();
    void parseValue();
    bool stringToBool(std::string stringValue);
    

    public:
        void parse();
        std::string readJsonFromFile(const std::string& filename);
        Parser(const std::string& input);
        void printMap();
};