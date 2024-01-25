#ifndef LEAF_H
#define LEAF_H

enum class leafID {PLUS, MIN, MULTIPLICATION, DIVIDE, POWER, NUMBER, INVALID=-1};

struct leaf
{   
    leaf() {};
    leaf(leaf* left, leaf* right, const std::string c, const leafID id, const double num) : 
        left(left), right(right), c(c), id(id), num(num) {};
    
    leaf* left;
    leaf* right;
    
    std::string c;
    leafID id;
    double num;
};

#endif