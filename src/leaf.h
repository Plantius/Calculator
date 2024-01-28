#ifndef LEAF_H
#define LEAF_H
#include <string>

enum class leafId 
{
    PLUS, MIN, MUL, DIV, 
    POW, TRIG, LOG, 
    DOUBLE, INT, INVALID=-1
};

struct leaf
{   
    leaf() : left(nullptr), right(nullptr), c({}), id(leafId::INVALID), intNum(0), doubleNum(0) {};
    leaf(leaf* left, leaf* right, const std::string c, const leafId id, const int intNum, const double doubleNum) : 
        left(left), right(right), c(c), id(id), intNum(intNum), doubleNum(doubleNum) {};
    
    leaf* left;
    leaf* right;

    std::string c;
    leafId id;
    int intNum;
    double doubleNum;
};

#endif