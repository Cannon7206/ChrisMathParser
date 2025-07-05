#ifndef MATHPARSER_LIBRARY_H
#define MATHPARSER_LIBRARY_H
#include "funct.h"
#include "token.h"
#include <algorithm>
#include <vector>
#include <memory>
#include <sstream>
#include <string>
#include <iostream>

double ApplyOp(double a, double b, char op);

bool isFunction(const std::string& word);



#endif //MATHPARSER_LIBRARY_H