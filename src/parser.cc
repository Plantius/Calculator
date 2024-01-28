#include "parser.h"
using std::cout, std::endl;

parser::parser()
{
    begin = nullptr;
} // Default Constructor

parser::~parser()
{
    deleteTree(begin);
    begin = nullptr;
} // Default Destructor


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
    std::vector<std::string> tokenizedInput = {}, prefix = {}, test = {};
    std::stringstream ss(input);
    std::string element = {};
    
    splitString(input, tokenizedInput);
    infixToPrefix(tokenizedInput, prefix);
    for (auto c : prefix){
        addBranch(start, c, getLeafID(c));
    }
    printTree();
    cout << endl;
    calculate();
} // createTree


bool parser::addBranch(leaf* &walker, const std::string c, const leafID id)
{
    bool done = false;

    if (begin == nullptr && walker == nullptr){
        begin = new leaf(nullptr, nullptr, c, id);
        walker = begin;
    }else if (isUnary(walker)){
        if (walker->id == leafID::TRIGONOMOTRY){
            if (walker->right != nullptr){
                done = addBranch(walker->right, c, id);
            }else {
                walker->right = new leaf(nullptr, nullptr, c, id);
                if (id == leafID::INT || id == leafID::DOUBLE){
                    walker->right->intNum = (id == leafID::INT ? atoi(c.c_str()) : 0);
                    walker->right->doublenum = (id == leafID::DOUBLE ? atof(c.c_str()) : 0); 
                }
                return true;
            }
            return done;
        }else {
            if (walker->left != nullptr){
                done = addBranch(walker->left, c, id);
            }else {
                walker->left = new leaf(nullptr, nullptr, c, id);
                if (id == leafID::INT || id == leafID::DOUBLE){
                    walker->left->intNum = (id == leafID::INT ? atoi(c.c_str()) : 0);
                    walker->left->doublenum = (id == leafID::DOUBLE ? atof(c.c_str()) : 0); 
                }
                return true;
            }
            if (!done){
                if (walker->right != nullptr){
                    done = addBranch(walker->right, c, id);
                }else {
                    walker->right = new leaf(nullptr, nullptr, c, id);
                    if (id == leafID::INT || id == leafID::DOUBLE){
                        walker->right->intNum = (id == leafID::INT ? atoi(c.c_str()) : 0);
                        walker->right->doublenum = (id == leafID::DOUBLE ? atof(c.c_str()) : 0); 
                    }
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
                        CALCULATE EXPRESSION
================================================================
*/


void parser::calculate() const
{
    leaf* walker = begin;

    recursionSimplify(walker);
    cout << "> ";
    printTree();
    cout << endl;
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
            walker->id = leafID::INT;
            walker->intNum = static_cast<int>(result);
        }else {
            walker->id = leafID::DOUBLE;
            walker->doublenum = result;
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
    case leafID::PLUS: 
        return (walker->left->id == leafID::INT ? walker->left->intNum : walker->left->doublenum) + 
               (walker->right->id == leafID::INT ? walker->right->intNum : walker->right->doublenum);
        
    case leafID::MIN: 
        return (walker->left->id == leafID::INT ? walker->left->intNum : walker->left->doublenum) -
               (walker->right->id == leafID::INT ? walker->right->intNum : walker->right->doublenum);
    case leafID::MULTIPLICATION: 
        return (walker->left->id == leafID::INT ? walker->left->intNum : walker->left->doublenum) *
               (walker->right->id == leafID::INT ? walker->right->intNum : walker->right->doublenum);
    case leafID::DIVIDE: 
        if ((walker->right->id == leafID::INT ? walker->right->intNum : walker->right->doublenum) == 0){
            throw parseError("Division by zero.");
        }
        return (walker->left->id == leafID::INT ? walker->left->intNum : walker->left->doublenum) / 
               (walker->right->id == leafID::INT ? walker->right->intNum : walker->right->doublenum);
    case leafID::POWER: 
        return pow((walker->left->id == leafID::INT ? walker->left->intNum : walker->left->doublenum), 
               (walker->right->id == leafID::INT ? walker->right->intNum : walker->right->doublenum));
    case leafID::TRIGONOMOTRY:
        if (walker->c == "sin"){
            return sin((walker->right->id == leafID::INT ? walker->right->intNum : walker->right->doublenum));
        }else if (walker->c == "cos"){
            return cos((walker->right->id == leafID::INT ? walker->right->intNum : walker->right->doublenum));
        }else if (walker->c == "tan"){
            return tan((walker->right->id == leafID::INT ? walker->right->intNum : walker->right->doublenum));
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
    
} // printTree


void parser::recursionPrintTree(leaf* &walker) const
{
    if (walker == nullptr){
        return;
    }    
    recursionPrintTree(walker->left);
    if (walker->id == leafID::INT || walker->id == leafID::DOUBLE){
    std::cout << (walker->id == leafID::INT ? walker->intNum : walker->doublenum);  
    }else {
        std::cout << walker->c;
        if (walker->id == leafID::TRIGONOMOTRY){
            std::cout << "(";
        }
    }
    recursionPrintTree(walker->right);
    if (walker->id == leafID::TRIGONOMOTRY){
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
            while (st.top() != "("){
                postfix.push_back(st.top());
                st.pop();
            }
            st.pop();
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