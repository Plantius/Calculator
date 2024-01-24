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