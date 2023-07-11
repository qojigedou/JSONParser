#include "inputDriver.h"
#include "lexer.h"
#include "token.h"
#include "parserFunc.h"

int main() {
    std::string input = "{ \"isTrue\": [true, true], \"ages\": 3}";
    InputDriver inputDrv(input);
    Lexer lex(inputDrv);

    std::cout << "\n\nparser version\n\n";

    Parser parser(input);
    parser.parse();

}