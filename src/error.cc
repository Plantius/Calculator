/**
* Implementation of the error handler
* Niels Versteeg (s3322637)
* error.cc
* 28-01-2024
**/

#include "error.h"

void errorHandler::printError() const {
    std::cerr << std::string(((this->getError()).length()+2), '-') << std::endl 
        << this->getRow() << ":" << this->getCol() << ": " << 
            int(this->getType()) << ":\n  " << this->getError() << std::endl
        << std::string(((this->getError()).length()+2), '-') << std::endl;
} // printError