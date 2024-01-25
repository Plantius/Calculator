#ifndef PARSER_H
#define PARSER_H
#include "standard.h"
#include <stack>

class parser
{
    private:
        leaf* begin;
    public:
        parser();
        ~parser();

        std::string infixToPostfix(const std::string infix) const;
        std::string infixToPrefix(const std::string infix) const;
        
        void createTree(const std::string input);
        bool addBranch(leaf* &walker, const std::string c, const leafID id);

        void printTree() const;
        void recursionPrintTree(leaf* &walker) const;

        bool calculate();
        void recursionSimplify(leaf* &walker) const;

        int calculateBranch(leaf* &walker) const;
};


#endif