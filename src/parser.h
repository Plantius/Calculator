#ifndef PARSER_H
#define PARSER_H
#include "standard.h"
#include <stack>

class parser
{
    private:
        char cursorChar;

        leaf* begin;
    public:
        parser() : cursorChar('>'), begin(nullptr) {};
        ~parser();

        void deleteTree(leaf* &walker) const;

        void infixToPostfix(const std::vector<std::string> infix, std::vector<std::string> &postfix) const;
        void infixToPrefix(const std::vector<std::string> infix, std::vector<std::string> &prefix) const;
        
        void createTree(const std::string input);
        bool addBranch(leaf* &walker, const std::string c, const leafID id);

        void printTree() const;
        void recursionPrintTree(leaf* &walker) const;

        void calculate() const;
        void recursionSimplify(leaf* &walker) const;

        double calculateBranch(leaf* &walker) const;
};


#endif