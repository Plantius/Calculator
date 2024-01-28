/**
* Implementation of the error handler
* Niels Versteeg (s3322637)
* error.cc
* 28-01-2024
**/

#include "error.h"

memoryError::memoryError(const std::string error){
    this->error = error;
    this->type = errorHandler::MEMORY;
}// default memory error constructor

parseError::parseError(const std::string error){
    this->error = error;
    this->type = errorHandler::PARSE;
}// default syntax error constructor

tokenError::tokenError(const std::string error, const int row, const int col){
    this->error = error;
    this->row = row;
    this->col = col;
    this->type = errorHandler::TOKEN;
}// default token error constructor

inputError::inputError(const std::string error){
    this->error = error;    
    this->type = errorHandler::INPUT;
}// default token error constructor

void errorHandler::printError() const {
    std::cerr << std::string(((this->getError()).length()+4), '-') << std::endl 
        << this->getRow() << ":" << this->getCol() << ": " << this->getType() << ":\n\t " << this->getError() << std::endl 
        << std::string((this->getError()).length(), '-') << std::endl;
} // printError