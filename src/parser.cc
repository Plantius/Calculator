#include "parser.h"

parser::parser()
{
    begin = nullptr;
} // Default Constructor

parser::~parser()
{
    deleteTree(begin);
} // Default Destructor

void parser::deleteTree(leaf* &walker) const
{
    if (walker == nullptr){
        return;
    }

    deleteTree(walker->left);
    deleteTree(walker->right);

    delete walker;
} // deleteTree


/*
================================================================
                        CREATE TREE
================================================================
*/


void parser::createTree(const std::string input)
{
    leaf* start = nullptr;
    std::string prefix = infixToPrefix(input);
    std::cout << prefix << std::endl;

    for (auto c : prefix){
        addBranch(start, c, getLeafID(c));
    }
    printTree();

} // createTree


bool parser::addBranch(leaf* &walker, const char c, const leafID id)
{
    bool done = false;

    if (begin == nullptr && walker == nullptr){
        begin = new leaf(nullptr, nullptr, c, id);
        walker = begin;
    }else if (isUnary(walker)){
        if (walker->left != nullptr){
            done = addBranch(walker->left, c, id);
        }else {
            walker->left = new leaf(nullptr, nullptr, c, id);
            return true;
        }
        if (!done){
            if (walker->right != nullptr){
                done = addBranch(walker->right, c, id);
            }else {
                walker->right = new leaf(nullptr, nullptr, c, id);
                return true;
            }
            return done;
        }else {
            return true;
        }
    }
    return false;
} // addBranch


/*
================================================================
                        PRINT TREE
================================================================
*/

void parser::printTree() const
{
    leaf* walker = begin;
    recursionPrintTree(walker);
    std::cout << std::endl;
} // printTree


void parser::recursionPrintTree(leaf* &walker) const
{
    if (walker == nullptr){
        return;
    }    

    recursionPrintTree(walker->left);

    std::cout << walker->c;

    recursionPrintTree(walker->right);

} // recursionPrintTree


/*
================================================================
                        INFIX_TO_PREFIX
================================================================
*/


std::string parser::infixToPostfix(const std::string infix) const
{
    std::stack<char> st;
    std::string postfix = {};

    for (auto c : infix){
        if (isalnum(c)){
            postfix += c;
        }else if (c == '('){
            st.push(c);
        }else if (c == ')'){
            while (st.top() != '('){
                postfix += st.top();
                st.pop();
            }
            st.pop();
        }else if (c == '-' || c == '+' || c == '*' || c == '/' || c == '^'){
            while (!st.empty() && (precedence(c) < precedence(st.top()) || 
                   (precedence(c) == precedence(st.top()) && c != '^'))){
                postfix += st.top();
                st.pop();
            }
            st.push(c);
        }
    }
    while (!st.empty()){
        postfix += st.top();
        st.pop();
    }

    return postfix;
} // infixToPostfix

std::string parser::infixToPrefix(const std::string infix) const
{
    std::string prefix = {};

    // Reverse the expression
    prefix = reverseString(infix);

    // Infix to Postfix
    prefix = infixToPostfix(prefix);

    // Reverse Postfix to get Prefix
    prefix = reverseString(prefix);

    return prefix;
} // infixToPrefix