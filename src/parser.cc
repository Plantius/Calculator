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
    std::vector<std::string> tokenizedInput = {}, prefix = {};
    std::stringstream ss(input);
    std::string element = {};
    
    while(ss >> element){
        if (!legalInput(element)){
            throw inputError("Invalid input.");
        }    
    }

    infixToPrefix(tokenizedInput, prefix);
    for (auto c : prefix){
        std::cout << c << std::endl;
        // addBranch(start, c, getLeafID(c));
    }
    printTree();
    calculate();
} // createTree


bool parser::addBranch(leaf* &walker, const std::string c, const leafID id)
{
    bool done = false;

    if (begin == nullptr && walker == nullptr){
        begin = new leaf(nullptr, nullptr, c, id, atof(c.c_str()));
        walker = begin;
    }else if (isUnary(walker)){
        if (walker->left != nullptr){
            done = addBranch(walker->left, c, id);
        }else {
            walker->left = new leaf(nullptr, nullptr, c, id, atof(c.c_str()));
            return true;
        }
        if (!done){
            if (walker->right != nullptr){
                done = addBranch(walker->right, c, id);
            }else {
                walker->right = new leaf(nullptr, nullptr, c, id, atof(c.c_str()));
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

bool parser::calculate() const
{
    // leaf* walker = begin;

    // recursionSimplify(walker);
    return false;
} // calculate

void parser::recursionSimplify(leaf* &walker) const
{
    if (walker == nullptr){
        return;
    }
    double result = 0;

    recursionSimplify(walker->left);
    recursionSimplify(walker->right);

    result = calculateBranch(walker);
    if (floor(result) == result){
        result = static_cast<int>(result);
    }
    walker->id = leafID::NUMBER;
    walker->c = char(result);
    walker->num = atof(walker->c.c_str());

    delete walker->left;
    delete walker->right;
    walker->left = nullptr, walker->right = nullptr;
} // recursionSimplify


double parser::calculateBranch(leaf* &walker) const
{
    if (isUnary(walker)){
        switch (walker->id)
        {
        case leafID::PLUS:
            return walker->left->num + walker->right->num;
        case leafID::MIN:
            return walker->left->num - walker->right->num;
        case leafID::MULTIPLICATION:
            return walker->left->num * walker->right->num;
        case leafID::DIVIDE:
            return walker->left->num / walker->right->num;
        case leafID::POWER:
            return pow(walker->left->num, walker->right->num);
        
        default:
            break;
        }
    }
    return -1;
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


void parser::infixToPostfix(const std::vector<std::string> infix, std::vector<std::string> &postfix) const
{
    std::stack<std::string> st;

    for (auto c : infix){
        if (atof(c.c_str())){
            postfix.push_back(c);
        }else if (c == "("){
            st.push(c);
        }else if (c == ")"){
            while (st.top() != "("){
                postfix.push_back(st.top());
                st.pop();
            }
            st.pop();
        }else if (c == "-" || c == "+" || c == "*" || c == "/" || c == "^"){
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