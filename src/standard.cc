#include "standard.h"
#include <cmath>
#include <sstream>
#include <unordered_map>

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

prec precedence(const std::string c)
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
    };
    auto it = precedenceMap.find(c);
    return (it != precedenceMap.end() ? it->second : prec::INVALID);
} // precedence

bool isUnary(const leaf* branch)
{
    return ((branch->id != leafId::INVALID && branch->id != leafId::INT && branch->id != leafId::DOUBLE) ? true : false);
} // isUnary

leafId getLeafID(const std::string c)
{
    std::stringstream ss(c);
    double tempDouble = {};
    if (ss >> tempDouble){
        return (tempDouble == floor(tempDouble) ? leafId::INT : leafId::DOUBLE);
    }
    if (c == "^"){
        return leafId::POWER;
    }else if (c == "*"){
        return leafId::MULTIPLICATION;
    }else if (c == "/"){
        return leafId::DIVIDE;
    }else if (c == "+"){
        return leafId::PLUS;
    }else if (c == "-"){
        return leafId::MIN;
    }else if (c == "sin" || c == "cos" || c == "tan"){
        return leafId::TRIGONOMOTRY;
    }
    return leafId::INVALID;
} // getLeafID


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
        if (std::isspace(c)){
            continue;
        }
        if (isdigit(c) || c == '.'){
            if (op){
                if ((temp == "-" || temp == "+") && 
                    (output.empty() || (!isNumber(output.back()) && output.back() != ")"))){
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