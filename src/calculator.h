#ifndef CALCULATOR_H
#define CALCULATOR_H
#include "standard.h"

class calculator
{
    private:
        leaf* begin;
    public:
        calculator();
        calculator(leaf* start);

        void simplify() const;
        void recursionSimplify(leaf* &walker) const;

        void calculateBranch(leaf* &walker) const;
};


#endif