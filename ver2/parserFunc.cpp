#include "parserFunc.h"


// <Json> ::= <Object>
//          | <Array>

// <Object> ::= '{' '}'
//            | '{' <Members> '}'

// <Members> ::= <Pair>
//             | <Pair> ',' <Members>

// <Pair> ::= String ':' <Value>

// <Array> ::= '[' ']'
//           | '[' <Elements> ']'

// <Elements> ::= <Value>
//              | <Value> ',' <Elements>

// <Value> ::= String
//           | Number
//           | <Object>
//           | <Array>
//           | true
//           | false
//           | null

bool Parser::stringToBool(std::string stringValue) {
   return stringValue == std::string("true") ? true : false;
}


std::string Parser::readJsonFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}
Parser::Parser(const std::string& input)
    : lexer(input), token(lexer.getToken()) {}


void Parser::parse(){
    try{
        std::cout << "parse()\n";
        parseJSON();
        std::cout << "Parsed successfully\n\n";
        printMap();
    }
    catch(std::exception& e){
        std::cerr << "Parsing failed: " << e.what() << "\n\n";
    }
}

void Parser::parseJSON(){
    std::cout << "parseJSON()\n";
    if(token.type == Token::LBRA){
        parseObject();
    }
    else if(token.type == Token::LSQBRA){
        parseArray();
    }
    else{
        throw std::runtime_error("Invalid JSON");
    }
}

void Parser::parseObject(){
    std::cout << "parseObject()\n";

    if(keys.empty()) {
        root.type = Parser::OBJECT;
        root.value = new std::map<std::string, Parser::JSONMember>;
        members.push(&root);
    } else {
        JSONMember *parent = members.top();
        if(parent->type == Parser::ARRAY) {
            root.type = Parser::ARRAY;
            root.value = new std::vector<Parser::JSONMember>;
            arrMember.push_back(&root);
        } else {
            auto map = reinterpret_cast<std::map<std::string, Parser::JSONMember>*>(parent->value);
            map->insert(std::pair<std::string, JSONMember>(keys.top(), JSONMember{}));
            members.push(&map->at(keys.top()));
        }
    }

    token = lexer.getToken();
    if(token.type == Token::RBRA) {
        members.pop();
        return;
    }
    if(token.type == Token::STRING) {
        keys.push(token.lexeme);
        parseMember();
    }
    else{
        throw std::runtime_error("Invalid parseObject");
    }
}

void Parser::parseArray(){
    std::cout << "parseArray()\n";

    root.type = Parser::ARRAY;
    root.value = new std::vector<Parser::JSONMember>;
    members.push(&root);
    //else if in array another array else if object in array
    // JSONMember* parent = members.top();
    // if (parent->type == Parser::ARRAY) {
    //     auto arr = reinterpret_cast<std::vector<Parser::JSONMember>*>(parent->value);
    //     arr->push_back(JSONMember{}); // Push a new element to the array
    //     members.push(&arr->back());
    // } else {
    //     auto map = reinterpret_cast<std::map<std::string, Parser::JSONMember>*>(parent->value);
    //     map->insert(std::pair<std::string, JSONMember>(keys.top(), JSONMember{}));
    //     members.push(&map->at(keys.top()));
    // }
    

    token = lexer.getToken();
    if(token.type == Token::RSQBRA){
        members.pop();
        
        return;
    }
    if(token.type == Token::STRING || token.type == Token::NUMBER) parseElements();
    else{
        throw std::runtime_error("Invalid parseArray");
    } 
}

void Parser::parseMember(){
    std::cout << "parseMember()\n";

    parsePair();
    if (token.type == Token::COMMA) {
        token = lexer.getToken();
        if (token.type == Token::STRING) {
            keys.push(token.lexeme);
            parseMember();  
        } else {
            throw std::runtime_error("Invalid parseMembers");
        }
    }
    keys.pop();
}

void Parser::parsePair(){
    std::cout << "parsePair()\n";
    token = lexer.getToken();
    if(token.type == Token::COLON) parseValue();
    else{
        throw std::runtime_error("Invalid parsePair");
    }
}   

void Parser::parseElements(){
    std::cout << "parseElements()\n";
    token = lexer.getToken();
    if(token.type != Token::EOI) parseValue();
    else throw std::runtime_error("Error: parseMembers error");

    if(token.type == Token::COMMA) parseElements();
}

void Parser::parseValue() {
    std::cout << "parseValue()\n";
    token = lexer.getToken();
    if (token.type == Token::STRING || token.type == Token::NUMBER || token.type == Token::NULL_VALUE || token.type == Token::BOOL_VALUE) {
        JSONMember member;
        switch (token.type) {
            case Token::STRING:
                member.value = new std::string(token.lexeme);
                member.type = Parser::STRING;
                break;
            case Token::NUMBER:
                member.value = new int(std::stoi(token.lexeme));
                // float or integer
                member.type = Parser::INTEGER;
                break;
            case Token::BOOL_VALUE:
                member.value = new bool(stringToBool(token.lexeme));
                member.type = Parser::BOOLEAN;
                break;
            case Token::NULL_VALUE:
                member.value = nullptr;
                member.type = Parser::NIL;
                break;
            default:
                throw std::runtime_error("Invalid value type");
        }

        JSONMember *parent = members.top();
        if(parent->type == Parser::ARRAY) {
            auto arr = reinterpret_cast<std::vector<JSONMember>*>(parent->value);
            arr->push_back(member);
        } else {
            auto map = reinterpret_cast<std::map<std::string, Parser::JSONMember>*>(parent->value);
            map->insert(std::pair<std::string, JSONMember>(keys.top(), member));
        }

        token = lexer.getToken();
    } else if (token.type == Token::LBRA) {
        parseObject();
    } else if (token.type == Token::LSQBRA) {
        parseArray();
    } else {
        throw std::runtime_error("Invalid value");
    }
}


void Parser::printMap() {
    std::cout << "Result Map:\n";
    for (const auto pair : *reinterpret_cast<std::map<std::string, JSONMember> *>(root.value)) {
        const std::string& key = pair.first;
        const JSONMember& value = pair.second;
        std::cout << "Key: " << key << " | Value: ";

        switch (value.type) {
            case Parser::STRING:
                std::cout << *reinterpret_cast<std::string*>(value.value);
                break;
            case Parser::INTEGER:
                std::cout << *reinterpret_cast<int*>(value.value);
                break;
            case Parser::BOOLEAN:
                std::cout << (*reinterpret_cast<bool*>(value.value) ? "true" : "false");
                break;
            case Parser::NIL:
                std::cout << "null";
                break;
            default:
                std::cout << "Unknown value type";
                break;
        }

        std::cout << "\n";
    }
}
