#ifndef PARSER_H
#define PARSER_H
#include "standard.h"
#include "calculator.h"
#include <stack>

class parser
{
    private:
        leaf* begin;
    public:
        parser();
        ~parser();

        void deleteTree(leaf* &walker) const;

        std::string infixToPostfix(const std::string infix) const;
        std::string infixToPrefix(const std::string infix) const;
        
        void createTree(const std::string input);
        bool addBranch(leaf* &walker, const char c, const leafID id);

        void printTree() const;
        void recursionPrintTree(leaf* &walker) const;

        bool calculate();
};


#endif