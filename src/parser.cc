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
    
    splitString(input, test);
    for (auto c : test){
        cout << c << endl;
    }

    while(ss >> element){
        tokenizedInput.push_back(element);
    }

    infixToPrefix(tokenizedInput, prefix);
    for (auto c : prefix){
        addBranch(start, c, getLeafID(c));
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
        if (walker->id == leafID::TRIGONOMOTRY){
            if (walker->right != nullptr){
                done = addBranch(walker->right, c, id);
            }else {
                walker->right = new leaf(nullptr, nullptr, c, id, atof(c.c_str()));
                return true;
            }
            return done;
        }else {
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
    cout << ": ";
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
            result = static_cast<int>(result);
        }
        walker->id = leafID::NUMBER;
        walker->c = std::to_string(result);
        walker->num = result;

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
        return walker->left->num + walker->right->num;
    case leafID::MIN:
        return walker->left->num - walker->right->num;
    case leafID::MULTIPLICATION:
        return walker->left->num * walker->right->num;
    case leafID::DIVIDE:
        return walker->left->num / walker->right->num;
    case leafID::POWER:
        return pow(walker->left->num, walker->right->num);
    case leafID::TRIGONOMOTRY:
        if (walker->c == "sin"){
            return sin(walker->right->num);
        }else if (walker->c == "cos"){
            return cos(walker->right->num);
        }else if (walker->c == "tan"){
            return tan(walker->right->num);
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
    if (walker->id == leafID::NUMBER){
        if (floor(walker->num) == walker->num){
            std::cout << int(walker->num);
        }else {
            std::cout << walker->num;
        }
    }else {
        std::cout << walker->c;
    }
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