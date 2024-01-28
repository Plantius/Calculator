#ifndef LEAF_H
#define LEAF_H
#include <string>

enum class leafID {PLUS, MIN, MULTIPLICATION, DIVIDE, 
                   POWER, TRIGONOMOTRY, LOGARITHM, 
                   DOUBLE, INT, INVALID=-1};

struct leaf
{   
    leaf() {};
    leaf(leaf* left, leaf* right, const std::string c, const leafID id) : 
        left(left), right(right), c(c), id(id) {};
    
    leaf* left;
    leaf* right;

    std::string c;
    leafID id;
    int intNum;
    double doublenum;
};

#endif