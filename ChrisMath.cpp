#include "ChrisMath.h"



double ApplyOp(const double a, const double b, const char op) {
    double result = 0;
    switch (op) {
        case '+':
            return result = a + b;

        case '-':
            return result = a - b;

        case '*':
            return result = a * b;

        case '/':
            return result = a / b;

        case '^':
            return result = funct::power(a, b);

        default:
            break;
    }
    return result;
}
bool isFunction(const std::string& word) {
    if (word=="sin"||word=="cos"||word=="tan"||word=="ln"||word=="e"||word=="sin^-1"||word=="cos^-1"||word=="tan^-1") {
        return true;
    }
    else {
        return false;
    }
}




