#ifndef STANDARD_H
#define STANDARD_H
#include "leaf.h"
#include "error.h"
#include <vector>
#include <string>


enum class prec 
{
    PLUS = 1, MIN = 1, TRIG = 3, 
    LOG = 3, MUL = 2, DIV = 2, 
    POW = 3, INVALID = -1
};

// Reverses the std::string input, and writes the reversed
// string to std::string reverse
void reverseString(const std::vector<std::string> input, std::vector<std::string> &output);

prec precedence(const std::string c);

bool isUnary(const leaf* branch);
leafId getLeafID(const std::string c);

bool legalInput(const std::string input);

void splitString(const std::string input, std::vector<std::string> &output);

bool isNumber(const std::string input);

#endif