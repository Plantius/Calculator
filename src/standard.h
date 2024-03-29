#ifndef STANDARD_H
#define STANDARD_H

#include "leaf.h"
#include "error.h"
#include <vector>
#include <string>

const double E = 2.718281828459045;
const double PI = 3.141592653589793;
const double FLOAT_ERROR = 1e-6;

enum class prec 
{
    PLUS = 1, MIN = 1, MUL = 2, DIV = 2, 
    POW = 3, LOG = 3, TRIG = 3, INVALID = -1
};

// Reverses the std::string input, and writes the reversed
// string to std::string reverse
void reverseString(const std::vector<std::string> input, std::vector<std::string> &output);


bool isUnary(const leaf* branch);

bool legalInput(const std::string input);

void splitString(const std::string input, std::vector<std::string> &output);

bool isNumber(const std::string input);

#endif