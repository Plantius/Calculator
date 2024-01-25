#ifndef LEAF_H
#define LEAF_H

enum class leafID {PLUS, MIN, TIMES, DIVIDE, POWER, NUMBER, INVALID=-1};

struct leaf
{   
    leaf() {};
    leaf(leaf* l, leaf* r, const std::string ch, const leafID ID) : left(l), right(r), c(ch), id(ID) {};
    leaf* left;
    leaf* right;
    std::string c;
    leafID id;
};

#endif