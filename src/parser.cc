#include "parser.h"

parser::parser()
{
    begin = nullptr;
} // Default Constructor

parser::~parser()
{
    deleteTree(begin);
    begin = nullptr;
} // Default Destructor


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
        addBranch(start, std::string(1, c), getLeafID(c));
    }
    printTree();
    calculate();
} // createTree


bool parser::addBranch(leaf* &walker, const std::string c, const leafID id)
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
        }
        return done;
    }
    return false;
} // addBranch


/*
================================================================
                        CALCULATE EXPRESSION
================================================================
*/

bool parser::calculate()
{
    // leaf* walker = begin;

    // recursionSimplify(walker);
} // calculate

void parser::recursionSimplify(leaf* &walker) const
{
    // if (walker == nullptr){
    //     return;
    // }
    // int result = 0;

    // recursionSimplify(walker->left);
    // recursionSimplify(walker->right);

    // result = calculateBranch(walker);
    // walker->id = leafID::NUMBER;
    // walker->c = char(result);
    // delete walker->left;
    // delete walker->right;
    // walker->left = nullptr, walker->right = nullptr;
} // recursionSimplify


int parser::calculateBranch(leaf* &walker) const
{
    // if (isUnary(walker)){
    //     switch (walker->id)
    //     {
    //     case leafID::PLUS:
    //         return atoi(walker->left->c.c_str()) + atoi(walker->right->c.c_str());
    //     case leafID::MIN:
    //         return atoi(walker->left->c.c_str()) - atoi(walker->right->c.c_str());
    //     case leafID::TIMES:
    //         return atoi(walker->left->c.c_str()) * atoi(walker->right->c.c_str());
    //     case leafID::DIVIDE:
    //         return atoi(walker->left->c.c_str()) / atoi(walker->right->c.c_str());
    //     case leafID::POWER:
    //         return pow(atoi(walker->left->c.c_str()), atoi(walker->right->c.c_str()));
        
    //     default:
    //         break;
    //     }
    // }
    // return -1;
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