#include "parser.h"

parser::parser()
{
    
} // Default Constructor


void parser::createTree(const std::string input) const
{
    std::string prefix = infixToPrefix(input);
    std::cout << prefix << std::endl;
} // createTree

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
    std::cout << prefix << std::endl;
    // Reverse Postfix to get Prefix
    prefix = reverseString(prefix);

    return prefix;
} // infixToPrefix