#ifndef STANDARD_H
#define STANDARD_H
#include <iostream>

enum class prec {PLUS = 1, MIN = 1, MUL = 2, DIV = 2, POW = 3, INVALID = -1};

// Reverses the std::string input, and writes the reversed
// string to std::string reverse
std::string reverseString(const std::string input);

prec precedence(const char c);

#endif