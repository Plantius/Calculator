#ifndef LEAF_H
#define LEAF_H

enum class leafID {PLUS, MIN, MULTIPLICATION, DIVIDE, POWER, NUMBER, INVALID=-1};

struct leaf
{   
    leaf() {};
    leaf(leaf* l, leaf* r, const std::string ch, const leafID ID, const double n) : 
        left(l), right(r), c(ch), id(ID), num(n) {};
    leaf* left;
    leaf* right;
    std::string c;
    leafID id;
    double num;
};

#endif