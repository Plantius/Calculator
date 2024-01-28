/**
* Declaratie van de error handler
* @author Niels Versteeg (s3322637)
* @author Lana van Sprang (s3272192)
* @file error.h
* @date 15-11-2023
**/

#ifndef ERROR_H
#define ERROR_H
#include <iostream>

enum class errorType 
{
    MEMORY, INPUT, PARSE, TOKEN
};

// Base error class
class errorHandler{
    public:
        // Constructor
        errorHandler() : error(), type(), row(1), col(1) {};

        /**
        * @function: getError
        * @abstract: Geeft de error string terug.
        **/
        std::string getError() const {return error;};
        
        /**
        * @function: getType
        * @abstract: Geeft de error type string terug.
        **/
        errorType getType() const {return type;};

        int getRow() const {return row;};
        
        int getCol() const {return col;};

        /**
        * @function: printError
        * @abstract: Print de gegeven error naar cout
        **/
        void printError() const;
    protected:
        std::string error;      // Error message
        errorType type;       // Error type
        int row, col;
}; // errorHandler

// Handles memory errors
class memoryError : public errorHandler{
    public:
        /**
        * @function: memoryError
        * @abstract: Constructor
        * @param err: set error to err 
        **/
        memoryError(const std::string err) : errorHandler() {error = err; type = errorType::MEMORY;};
}; // memoryError

// Handles input errors
class inputError : public errorHandler{
    public:
        /**
        * @function: inputError
        * @abstract: Constructor
        * @param err: set error to err 
        **/
        inputError(const std::string err)  : errorHandler() {error = err; type = errorType::INPUT;};
}; // inputError

// Handles input errors
class parseError : public errorHandler{
    public:
        /**
        * @function: parseError
        * @abstract: Constructor
        * @param err: set error to err 
        **/
        parseError(const std::string err)  : errorHandler() {error = err; type = errorType::PARSE;};
}; // inputError

// Handles input errors
class tokenError : public errorHandler{
    public:
        /**
        * @function: tokenError
        * @abstract: Constructor
        * @param err: set error to err 
        **/
        tokenError(const std::string err,
                   const int row, const int col)  : errorHandler() {error = err; type = errorType::TOKEN; this->row = row; this->col = col;};
}; // inputError


#endif