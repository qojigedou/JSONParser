#include "inputDriver.h"

InputDriver::InputDriver(std::string inputStr){
    inputData = inputStr;
    pos = 0;
}

char InputDriver::getChar(){
    return (pos < inputData.length()) ? inputData[pos++] : '\0';
}

char InputDriver::writeBack(){
    if(pos > 0){
        pos--;
    }
    
    return inputData[pos];
}