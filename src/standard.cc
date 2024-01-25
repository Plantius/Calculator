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
    if (isalnum(c[0])){
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