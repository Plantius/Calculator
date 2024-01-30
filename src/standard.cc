#include "standard.h"
#include <math.h>
#include <sstream>

void reverseString(const std::vector<std::string> input, std::vector<std::string> &output)
{   
    for (size_t i = input.size(); i > 0; i--){
        if (input[i-1] == "("){
            output.push_back(")");
        }else if (input[i-1] == ")"){
            output.push_back("(");
        }else {
            output.push_back(input[i-1]);
        }
    }
} // reverseString




bool isUnary(const leaf* branch)
{
    return (branch->id != leafId::INVALID && branch->id != leafId::INT && branch->id != leafId::DOUBLE);
} // isUnary


bool legalInput (const std::string input)
{
    for (auto c : input){
        if (!isascii(c)){
            return false;
        }
    }
    return true;
} // legalInput


void splitString(const std::string input, std::vector<std::string> &output)
{
    std::string temp = {};
    bool num = false, op = false;

    for (auto c : input){
        if (isspace(c)){
            continue;
        }
        if (isdigit(c) || c == '.'){
            if (op){
                if ((temp == "-" || temp == "+") && 
                    (output.empty() || (!isNumber(output.back()) && output.back() != ")" && 
                                        output.back() != "ans" && output.back() != "e" && output.back() != "pi"))){
                    temp += c;
                    num = true, op = false;
                    continue;
                }
                output.push_back(temp);
                temp.clear();
                op = false;
            }
            temp += c;
            num = true;
        }else {
            if (isalpha(c)){
                if (num){
                    output.push_back(temp);
                    temp.clear();
                    num = false;
                }else if (temp == "+" || temp == "-" || temp == "*" || temp == "/" || 
                      temp == "^" || temp == "(" || temp == ")"){
                    output.push_back(temp);
                    temp.clear();
                }
                temp += c;
                op = true;
            }else if (c == '+' || c == '-' || c == '*' || c == '/' || 
                      c == '^' || c == '(' || c == ')'){
                if (num || temp.size() >= 1){
                    output.push_back(temp);
                    temp.clear();
                    num = false;
                }
                temp += c;
                op = true;
            }
        }
    }
    output.push_back(temp);
} // splitString

bool isNumber(const std::string input)
{
    for (auto c : input){
        if (isdigit(c)){
            return true;
        }
    }
    return false;
} // isNumber