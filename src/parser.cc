#include "parser.h"
#include <cmath>
#include <stack>
#include <sstream>
#include <iostream>
#include <unordered_map>

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
    // for (auto p : results){
    //     std::cout << p.first <<", " << p.second <<std::endl;
    // }
    // Adds all tokens to a tree
    for (auto c : prefix){
        addBranch(start, convertChar(c), getLeafID(c)) ? 0 : throw parseError("Invalid tree branch.");
    }
    checkTree() ? 0 : throw parseError("The tree is invalid.");
    printTree();
    calculate();
    results.push_back(std::make_pair(begin->intNum, begin->doubleNum));
    std::cout << results.back().first << "," << results.back().second << std::endl;

    checkTree() ? 0 : throw parseError("The tree is invalid.");
} // createTree


bool parser::addBranch(leaf* &walker, const std::string c, const leafId id)
{
    bool done = false;

    if (begin == nullptr && walker == nullptr){
        begin = new leaf(nullptr, nullptr, c, id, 
            (id == leafId::INT || id == leafId::DOUBLE ? atoi(c.c_str()) : 0), 
            (id == leafId::DOUBLE || id == leafId::INT ? atof(c.c_str()) : 0));
        walker = begin;
        return true;
    }else if (isUnary(walker)){
        if (walker->id == leafId::TRIG || walker->id == leafId::LOG){
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
        if (walker->id == leafId::TRIG || walker->id == leafId::LOG){
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
        walker->id = ((fabs(result) - FLOAT_ERROR) < 0 ? leafId::INT : leafId::DOUBLE);
        walker->intNum = static_cast<int>(result);
        walker->doubleNum = result;
        std::cout << int(result) << " " << result << std::endl;
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
    case leafId::LOG:
        if (walker->c == "ln"){
            return log((walker->right->id == leafId::INT ? walker->right->intNum : walker->right->doubleNum));
        }else if (walker->c == "log"){
            return log10((walker->right->id == leafId::INT ? walker->right->intNum : walker->right->doubleNum));
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
    std::cout << (walker->id == leafId::INT ? walker->intNum : walker->doubleNum);  
    }else {
        std::cout << walker->c;
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
        if (ss >> temp || c == "pi" || c == "e" || c == "ans"){
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


/*
================================================================
                        HELP FUNCTIONS
================================================================
*/


leafId parser::getLeafID(const std::string c) const
{
    std::stringstream ss(c);
    double tempDouble = {};
    if (ss >> tempDouble){
        return ((fabs(tempDouble) - FLOAT_ERROR) < 0 ? leafId::INT : leafId::DOUBLE);
    }
    if (c == "ans"){
        return (!results.empty() ? (results.back().second == floor(results.back().second) ? leafId::INT : leafId::DOUBLE) : leafId::INVALID);
    }
    static const std::unordered_map<std::string, leafId> leafIdMap = 
    {
        {"^", leafId::POW},
        {"*", leafId::MUL},
        {"/", leafId::DIV},
        {"+", leafId::PLUS},
        {"-", leafId::MIN},
        {"sin", leafId::TRIG},
        {"cos", leafId::TRIG},
        {"tan", leafId::TRIG},
        {"ln", leafId::LOG},
        {"log", leafId::LOG},
        {"e", leafId::DOUBLE},
        {"pi", leafId::DOUBLE}
    };

    auto it = leafIdMap.find(c);
    return (it != leafIdMap.end()) ? it->second : leafId::INVALID;
} // getLeafID


prec parser::precedence(const std::string c) const
{
    static const std::unordered_map<std::string, prec> precedenceMap = 
    {
        {"^", prec::POW},
        {"*", prec::MUL},
        {"/", prec::DIV},
        {"+", prec::PLUS},
        {"-", prec::MIN},
        {"sin", prec::TRIG},
        {"cos", prec::TRIG},
        {"tan", prec::TRIG},
        {"ln", prec::LOG},
        {"log", prec::LOG}
    };

    auto it = precedenceMap.find(c);
    return (it != precedenceMap.end()) ? it->second : prec::INVALID;
} // precedence

std::string parser::convertChar(const std::string c)
{
    if (c == "e"){
        return std::to_string(E);
    }else if (c == "pi"){
        return std::to_string(PI);
    }else if (c == "ans"){
        return (!results.empty()? getLeafID(c) == leafId::INT ? std::to_string(results.back().first) : std::to_string(results.back().second) : 
            throw inputError("Invalid input: No previous answers."));
    }
    return c;
} // convertChar
