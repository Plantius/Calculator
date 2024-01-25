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

// Base error class
class errorHandler{
    public:
        // Constructor
        errorHandler() : error(), type(), row(1), col(1) {};

        /**
        * @function: getError
        * @abstract: Geeft de error string terug.
        **/
        std::string getError() const {return this->error;};
        
        /**
        * @function: getType
        * @abstract: Geeft de error type string terug.
        **/
        std::string getType() const {return this->type;};

        int getRow() const {return this->row;};
        
        int getCol() const {return this->col;};

        /**
        * @function: printError
        * @abstract: Print de gegeven error naar cout
        **/
        void printError() const;
    protected:
        std::string error;      // Error message
        std::string type;       // Error type
        int row, col;
        const std::string MEMORY = "Memory Error";
        const std::string INPUT = "Input Error";
        const std::string PARSE = "Parse Error";
        const std::string TOKEN = "Token Error";
}; // errorHandler

// Handles memory errors
class memoryError : public errorHandler{
    public:
        /**
        * @function: memoryError
        * @abstract: Constructor
        * @param err: set error to err 
        **/
        memoryError(const std::string err);
}; // memoryError

// Handles input errors
class inputError : public errorHandler{
    public:
        /**
        * @function: inputError
        * @abstract: Constructor
        * @param err: set error to err 
        **/
        inputError(const std::string err);
}; // inputError

// Handles input errors
class parseError : public errorHandler{
    public:
        /**
        * @function: parseError
        * @abstract: Constructor
        * @param err: set error to err 
        **/
        parseError(const std::string err, 
                   const int row, const int col);
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
                   const int row, const int col);
}; // inputError


#endif