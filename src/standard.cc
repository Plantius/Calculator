#include "standard.h"

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
    if (c == "^"){
        return prec::POW;
    }else if (c == "*"){
        return prec::MUL;
    }else if (c == "/"){
        return prec::DIV;
    }else if (c == "+"){
        return prec::PLUS;
    }else if (c == "-"){
        return prec::MIN;
    }else if (c == "sin" || c == "cos" || c == "tan"){
        return prec::TRIG;
    }
    return prec::INVALID;
} // precedence

bool isUnary(const leaf* branch)
{
    if (branch->id != leafID::INVALID && branch->id != leafID::NUMBER){
        return true;
    }
    return false;
} // isUnary

leafID getLeafID(const std::string c)
{
    std::stringstream ss(c);
    double temp = {};
    if (ss >> temp){
        return leafID::NUMBER;
    }
    if (c == "^"){
        return leafID::POWER;
    }else if (c == "*"){
        return leafID::MULTIPLICATION;
    }else if (c == "/"){
        return leafID::DIVIDE;
    }else if (c == "+"){
        return leafID::PLUS;
    }else if (c == "-"){
        return leafID::MIN;
    }else if (c == "sin" || c == "cos" || c == "tan"){
        return leafID::TRIGONOMOTRY;
    }
    return leafID::INVALID;
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
        if (c == ' '){
            continue;
        }
        if (isdigit(c) || c == '.'){
            if (op){
                if (output.empty() || (temp == "-" || temp == "+") && !isdigit(output.back()[0])){
                    temp += c;
                    num = true, op = false;
                    continue;
                }
                output.push_back(temp);
                temp.clear();
                temp += c;
                num = true, op = false;
            }else {
                temp += c;
                num = true;
            }
        }else if (!isdigit(c) && c != '.'){
            if (isalpha(c)){
                if (num){
                    output.push_back(temp);
                    temp.clear();
                    temp += c;
                    num = false, op = true;
                }else {
                    temp += c;
                    op = true;
                }
            }else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || 
                      c == '(' || c == ')'){
                if (num || temp.size() >= 1){
                    output.push_back(temp);
                    temp.clear();
                    temp += c;
                    num = false, op = true;
                }else {
                    temp += c;
                    op = true;
                }
            }
            
        }
    }
    output.push_back(temp);
} // splitString