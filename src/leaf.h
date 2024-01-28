#ifndef LEAF_H
#define LEAF_H
#include <string>

enum class leafID {PLUS, MIN, MULTIPLICATION, DIVIDE, 
                   POWER, TRIGONOMOTRY, LOGARITHM, 
                   DOUBLE, INT, INVALID=-1};

struct leaf
{   
    leaf() : left(nullptr), right(nullptr), c({}), id(leafID::INVALID), intNum(0), doubleNum(0) {};
    leaf(leaf* left, leaf* right, const std::string c, const leafID id, const int intNum, const double doubleNum) : 
        left(left), right(right), c(c), id(id), intNum(intNum), doubleNum(doubleNum) {};
    
    leaf* left;
    leaf* right;

    std::string c;
    leafID id;
    int intNum;
    double doubleNum;
};

#endif