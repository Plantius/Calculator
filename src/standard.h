#ifndef STANDARD_H
#define STANDARD_H
#include <iostream>
#include <math.h>
#include <vector>
#include "leaf.h"
#include "error.h"

enum class prec {PLUS = 1, MIN = 1, MUL = 2, DIV = 2, POW = 3, INVALID = -1};

// Reverses the std::string input, and writes the reversed
// string to std::string reverse
void reverseString(const std::vector<std::string> input, std::vector<std::string> &output);

prec precedence(const std::string c);

bool isUnary(const leaf* branch);
leafID getLeafID(const std::string c);

void deleteTree(leaf* &walker);

bool legalInput(const std::string input);
#endif