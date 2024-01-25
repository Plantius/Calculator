#ifndef PARSER_H
#define PARSER_H
#include "standard.h"
#include <stack>
#include <vector>
#include <sstream>

class parser
{
    private:
        leaf* begin;
    public:
        parser();
        ~parser();

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