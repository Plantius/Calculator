#ifndef PARSER_H
#define PARSER_H
#include "standard.h"
#include <stack>

class parser
{
    private:
        
    public:
        parser();
        
        std::string infixToPostfix(const std::string infix) const;
        std::string infixToPrefix(const std::string infix) const;
        void createTree(const std::string input) const;

};


#endif