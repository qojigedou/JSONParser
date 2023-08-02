#include "include/inputDriver.h"
#include "include/lexer.h"
#include "include/token.h"
#include "include/parser.h"

using namespace json;

int main() {
    std::string input = json::Parser::readJsonFromFile(std::string("test.json"));

    json::Parser parser(input);
    parser.parse();
    parser.printMap();

}
