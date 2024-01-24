#include "standard.h"

std::string reverseString(const std::string input)
{   
    std::string reverse = {};
    for (size_t i = input.size(); i > 0; i--){
        if (input[i-1] == '('){
            reverse += ')';
        }else if (input[i-1] == ')'){
            reverse += '(';
        }else {
            reverse += input[i-1];
        }
    }
    return reverse;
} // reverseString

prec precedence(const char c)
{
    switch (c)
    {
        case '^': return prec::POW;
        case '*': return prec::MUL;
        case '/': return prec::DIV;
        case '+': return prec::PLUS;
        case '-': return prec::MIN;

        default: return prec::INVALID;
    }
} // precedence

bool isUnary(const leaf* branch)
{
    switch (branch->c)
    {
    case '+': case '-': case '*': case '/': case '^': return true;
    default: return false;
    }
} // isUnary

leafID getLeafID(const char c)
{
    switch (c)
    {
    case '+': return leafID::PLUS;
    case '-': return leafID::MIN;
    case '*': return leafID::TIMES;
    case '/': return leafID::DIVIDE;
    case '^': return leafID::POWER;
    default: return leafID::INVALID;
    }
} // getLeafID