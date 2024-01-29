#include "parser.h"
#include <cmath>
#include <stack>
#include <sstream>
#include <iostream>

void parser::clearTree()
{
    deleteTree(begin);
    begin = nullptr;
} // clearTree

void parser::deleteTree(leaf* &walker) const
{
    if (walker == nullptr){
        return;
    }

    deleteTree(walker->left);
    deleteTree(walker->right);

    delete walker;
    walker = nullptr;
} // deleteTree


/*
================================================================
                        CREATE TREE
================================================================
*/


void parser::createTree(const std::string input)
{
    leaf* start = nullptr;
    std::vector<std::string> tokenizedInput = {}, prefix = {};
    std::stringstream ss(input);
    
    splitString(input, tokenizedInput);
    infixToPrefix(tokenizedInput, prefix);
    
    // Adds all tokens to a tree
    for (auto c : prefix){
        addBranch(start, c, getLeafID(c)) ? 0 : throw parseError("Invalid tree branch.");
    }
    
    checkTree() ? 0 : throw parseError("The tree is invalid.");
    printTree();
    calculate();
} // createTree


bool parser::addBranch(leaf* &walker, const std::string c, const leafId id)
{
    bool done = false;

    if (begin == nullptr && walker == nullptr){
        begin = new leaf(nullptr, nullptr, c, id, 
            (id == leafId::INT ? atoi(c.c_str()) : 0), 
            (id == leafId::DOUBLE ? atof(c.c_str()) : 0));
        walker = begin;
        return true;
    }else if (isUnary(walker)){
        if (walker->id == leafId::TRIG){
            if (walker->right != nullptr){
                done = addBranch(walker->right, c, id);
            }else {
                walker->right = new leaf(nullptr, nullptr, c, id, 
                    (id == leafId::INT ? atoi(c.c_str()) : 0), 
                    (id == leafId::DOUBLE ? atof(c.c_str()) : 0));
                return true;
            }
            return done;
        }else {
            if (walker->left != nullptr){
                done = addBranch(walker->left, c, id);
            }else {
                walker->left = new leaf(nullptr, nullptr, c, id, 
                    (id == leafId::INT ? atoi(c.c_str()) : 0), 
                    (id == leafId::DOUBLE ? atof(c.c_str()) : 0));
                return true;
            }
            if (!done){
                if (walker->right != nullptr){
                    done = addBranch(walker->right, c, id);
                }else {
                    walker->right = new leaf(nullptr, nullptr, c, id, 
                        (id == leafId::INT ? atoi(c.c_str()) : 0), 
                        (id == leafId::DOUBLE ? atof(c.c_str()) : 0));
                    return true;
                }
            }
            return done;
        }
    }
    return false;
} // addBranch


/*
================================================================
                            CHECK TREE
================================================================
*/


bool parser::checkTree() const
{
    leaf* walker = begin;

    return recursionCheckTree(walker);
} // checkTree


bool parser::recursionCheckTree(leaf* &walker) const
{
    if (walker == nullptr){
        return false;
    }

    if (isUnary(walker)){
        if (walker->id == leafId::TRIG){
            return (walker->right != nullptr);
        }
        return (walker->left != nullptr && walker->right != nullptr);
    }

    recursionCheckTree(walker->left);
    recursionCheckTree(walker->right);
    
    return true;
} // recursionCheckWalker

/*
================================================================
                        CALCULATE EXPRESSION
================================================================
*/


void parser::calculate() const
{
    leaf* walker = begin;

    recursionSimplify(walker);
    std::cout << cursorChar <<" ";
    printTree();
} // calculate

void parser::recursionSimplify(leaf* &walker) const
{
    if (walker == nullptr){
        return;
    }
    double result = 0;

    recursionSimplify(walker->left);
    recursionSimplify(walker->right);

    if (isUnary(walker)){
        result = calculateBranch(walker);

        if (floor(result) == result){
            walker->id = leafId::INT;
            walker->intNum = static_cast<int>(result);
        }else {
            walker->id = leafId::DOUBLE;
            walker->doubleNum = result;
        }
        walker->c = std::to_string(result);

        delete walker->left; 
        delete walker->right;
        walker->left = nullptr, walker->right = nullptr;
    }
} // recursionSimplify


double parser::calculateBranch(leaf* &walker) const
{
    switch (walker->id)
    {
    case leafId::PLUS: 
        return (walker->left->id == leafId::INT ? walker->left->intNum : walker->left->doubleNum) + 
               (walker->right->id == leafId::INT ? walker->right->intNum : walker->right->doubleNum);
        
    case leafId::MIN: 
        return (walker->left->id == leafId::INT ? walker->left->intNum : walker->left->doubleNum) -
               (walker->right->id == leafId::INT ? walker->right->intNum : walker->right->doubleNum);
    case leafId::MUL: 
        return (walker->left->id == leafId::INT ? walker->left->intNum : walker->left->doubleNum) *
               (walker->right->id == leafId::INT ? walker->right->intNum : walker->right->doubleNum);
    case leafId::DIV: 
        if ((walker->right->id == leafId::INT ? walker->right->intNum : walker->right->doubleNum) == 0){
            throw parseError("Division by zero. Right branch of leaf is zero.");
        }
        return (walker->left->id == leafId::INT ? walker->left->intNum : walker->left->doubleNum) / 
               (walker->right->id == leafId::INT ? walker->right->intNum : walker->right->doubleNum);
    case leafId::POW: 
        return pow((walker->left->id == leafId::INT ? walker->left->intNum : walker->left->doubleNum), 
               (walker->right->id == leafId::INT ? walker->right->intNum : walker->right->doubleNum));
    case leafId::TRIG:
        if (walker->c == "sin"){
            return sin((walker->right->id == leafId::INT ? walker->right->intNum : walker->right->doubleNum));
        }else if (walker->c == "cos"){
            return cos((walker->right->id == leafId::INT ? walker->right->intNum : walker->right->doubleNum));
        }else if (walker->c == "tan"){
            return tan((walker->right->id == leafId::INT ? walker->right->intNum : walker->right->doubleNum));
        }
        break;
    default: 
        throw parseError("Invalid unary operator.");
    }
    return 0;
} // calculateBranch


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
    if (walker->id == leafId::INT || walker->id == leafId::DOUBLE){
    std::cout << "N"<<(walker->id == leafId::INT ? walker->intNum : walker->doubleNum);  
    }else {
        std::cout <<"C"<< walker->c;
        if (walker->id == leafId::TRIG){
            std::cout << "(";
        }
    }
    recursionPrintTree(walker->right);
    if (walker->id == leafId::TRIG){
        std::cout << ")";
    }
} // recursionPrintTree


/*
================================================================
                        INFIX_TO_PREFIX
================================================================
*/


void parser::infixToPostfix(const std::vector<std::string> infix, std::vector<std::string> &postfix) const
{
    std::stack<std::string> st;
    double temp = {};

    for (auto c : infix){
        std::stringstream ss(c);
        if (ss >> temp){
            postfix.push_back(c);
        }else if (c == "("){
            st.push(c);
        }else if (c == ")"){
            while (!st.empty() && st.top() != "("){
                postfix.push_back(st.top());
                st.pop();
            }
            if (!st.empty()){
                st.pop();
            }else {
                throw parseError("Mismatched parantheses.");
            }
        }else{
            while (!st.empty() && (precedence(c) < precedence(st.top()) || 
                   (precedence(c) == precedence(st.top()) && c != "^"))){
                postfix.push_back(st.top());
                st.pop();
            }
            st.push(c);
        }
    }
    while (!st.empty()){
        postfix.push_back(st.top());
        st.pop();
    }
} // infixToPostfix

void parser::infixToPrefix(const std::vector<std::string> infix, std::vector<std::string> &prefix) const
{
    std::vector<std::string> reverse = {}, postfix = {};

    // Reverse the expression
    reverseString(infix, reverse);
    
    // Infix to Postfix
    infixToPostfix(reverse, postfix);
   
    // Reverse Postfix to get Prefix
    reverseString(postfix, prefix);
} // infixToPrefix