#include "include/parser.h"
#include "include/object.h"
#include "include/array.h"
#include "include/primitive.h"
#include <memory>

using namespace json;

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
    : lexer(input) {}

void Parser::parse(){
    try{
        token = lexer.getToken();

        parseJSON();
        std::cout << "Parsed successfully\n\n";
    }
    catch(std::exception& e){
        std::cerr << "Parsing failed: " << e.what() << "\n\n";
    }
}

bool Parser::accept(Token::Type type) {
    if(token.type == type) {
        token = lexer.getToken();
        return true;
    }
    
    return false;
}

void Parser::parseJSON(){

    if(accept(Token::LBRA)){
        parseObject();
    }
    else if(accept(Token::LSQBRA)){
        parseArray();
    }
    else{
        throw std::runtime_error("Invalid JSON");
    }
}

void Parser::parseObject(){

    json::Object *object = new Object();
    object->type = Member::OBJECT;
    if(root == nullptr) {
        root = object;
    } else {
        containers.top()->put(keys.top(), object);
    }
    containers.push(object);

    keys.push(token.lexeme);
    if(accept(Token::STRING)) {
        parseMembers();
    }

    containers.pop();

    if(!accept(Token::RBRA)) {
        throw std::runtime_error("Invalid parseObject");
    }
}

void Parser::parseArray(){

    json::Array *array = new Array();
    array->type = Member::ARRAY;
    if(root == nullptr) {
        root = array;
    } else {
        containers.top()->put(keys.top(), array);
    }
    containers.push(array);

    token = lexer.getToken();
    if(token.type == Token::STRING || token.type == Token::NUMBER || token.type == Token::LBRA
            || token.type == Token::LSQBRA || token.type == Token::BOOL_VALUE
            || token.type == Token::NULL_VALUE) {
        //std::cout << token.lexeme << std::endl;
        parseElements();
    }

    containers.pop();

    if(!accept(Token::RSQBRA)) {
        throw std::runtime_error("Invalid parseArray");
    }
}

void Parser::parseMembers(){
    parsePair();
    
    if(accept(Token::COMMA)) {
        keys.push(token.lexeme);
        if(!accept(Token::STRING)) {
            throw std::runtime_error("Invalid parseMembers");
        }

        parseMembers();
    }
}

void Parser::parsePair(){

    if(accept(Token::COLON)) {
        parseValue();
        keys.pop();
    }
    else{
        throw std::runtime_error("Invalid parsePair");
    }
}

void Parser::parseElements(){
    
    parseValue();

    if(accept(Token::COMMA)) {
        if(token.type == Token::STRING || token.type == Token::NUMBER || token.type == Token::LBRA
                || token.type == Token::LSQBRA || token.type == Token::BOOL_VALUE
                || token.type == Token::NULL_VALUE) {
            parseElements();
        } else {
            throw std::runtime_error("Invalid parseElements");
        }
    }
}

void Parser::parseValue() {

    if (token.type == Token::STRING || token.type == Token::NUMBER || token.type == Token::NULL_VALUE || token.type == Token::BOOL_VALUE) {
                            
        Primitive *primitive = new Primitive();
        switch (token.type) {
            case Token::STRING:
                primitive->data = new std::string(token.lexeme);
                primitive->type = Member::STRING;
                break;
            case Token::NUMBER:
                if(token.lexeme.find('.')){
                    primitive->data = new float(std::stof(token.lexeme));
                    primitive->type = Member::FLOAT;
                    break;
                }
                else{
                    primitive->data = new int(std::stoi(token.lexeme));
                    primitive->type = Member::INTEGER;
                    break;
                }
            case Token::BOOL_VALUE:
                primitive->data = new bool(stringToBool(token.lexeme));
                primitive->type = Member::BOOLEAN;
                break;
            case Token::NULL_VALUE:
                primitive->data = nullptr;
                primitive->type = Member::NIL;
                break;
            default:
                throw std::runtime_error("Invalid value type");
        }

        Container *parent = containers.top();
        parent->put(keys.top(), primitive);
        token = lexer.getToken();
    } else if (token.type == Token::LBRA) {
        token = lexer.getToken();
        parseObject();
    } else if (token.type == Token::LSQBRA) {
        parseArray();
    } else {
        throw std::runtime_error("Invalid value");
    }
}

void Parser::printMap(Member *top) {
    if(top->type == Member::ARRAY) {
        Array *array = (Array *) top;
        std::cout << "[ ";
        for(auto element : array->data) {
            printMap(element);
            std::cout << ", ";
        }
        std::cout << " ]";
    } else if(top->type == Member::OBJECT) {
        Object *object = (Object *) top;
        std::cout << "{ ";
        for(auto element : object->data) {
            std::cout << element.first << ": ";
            printMap(element.second);
            std::cout << ", ";
        }
        std::cout << " }";
    } else {
        switch (top->type) {
            case Member::STRING:
                std::cout << *reinterpret_cast<std::string*>(reinterpret_cast<Primitive *>(top)->data);
                break;
            case Member::INTEGER:
                std::cout << *reinterpret_cast<int*>(reinterpret_cast<Primitive *>(top)->data);
                break;
            case Member::FLOAT:
                std::cout << *reinterpret_cast<float*>(reinterpret_cast<Primitive *>(top)->data);
                break;
            case Member::BOOLEAN:
                std::cout << (*reinterpret_cast<bool*>(reinterpret_cast<Primitive *>(top)->data) ? "true" : "false");
                break;
            case Member::NIL:
                std::cout << "null";
                break;
        }
    }
}

void Parser::printMap() {
    //std::cout << ((Object *) root)->data.size() << std::endl;
    printMap(root);
    std::cout << "\n";
}
