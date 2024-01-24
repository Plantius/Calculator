#include "calculator.h"

calculator::calculator() 
{
    begin = nullptr;
} // Default Constructor

calculator::calculator(leaf* start) 
{
    begin = start;
} // Default Constructor


void calculator::simplify() const
{
    leaf* walker = begin;

    recursionSimplify(walker);
} // simplify


void calculator::recursionSimplify(leaf* &walker) const
{
    if (walker == nullptr){
        return;
    }

    recursionSimplify(walker->left);
    recursionSimplify(walker->right);

    calculateBranch(walker);
} // recursionSimplify


void calculator::calculateBranch(leaf* &walker) const
{
    int result = 0;
    if (isUnary(walker)){
        switch (walker->id)
        {
        case leafID::PLUS:
            result = (walker->left->c - '0') + (walker->right->c - '0');
            break;
        case leafID::MIN:
            result = (walker->left->c - '0') - (walker->right->c - '0');
            break;
        case leafID::TIMES:
            result = (walker->left->c - '0') * (walker->right->c - '0');
            break;
        case leafID::DIVIDE:
            result = (walker->left->c - '0') / (walker->right->c - '0');
            break;
        case leafID::POWER:
            result = pow((walker->left->c - '0'), (walker->right->c - '0'));
            break;
        
        default:
            break;
        }
    }
} // calculateBranch

