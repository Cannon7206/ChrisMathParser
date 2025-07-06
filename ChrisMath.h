#ifndef MATHPARSER_LIBRARY_H
#define MATHPARSER_LIBRARY_H
#pragma once
#include <algorithm>
#include <utility>
#include <vector>
#include <string>

#include "funct.h"

bool isFunction(const std::string &word);

enum class tokenType {
    NUMBER,
    OPERATOR,
    FUNCTION,
    PARENTHESIS,
};


struct token {
    tokenType type;
    std::string word;

    token(const tokenType t, std::string w) : type(t), word(std::move(w)) {
    }
};

class Tokenizer {
public:
    static std::vector<token> tokenize(const std::string &input);
};

class Parser {
public:
    static std::vector<token> infixToPostfix(const std::vector<token> &tokens);

private:
    static int getPrecedence(const std::string &op) ;

    static bool isLeftAssociative(const std::string &op) ;
};

class Evaluator {
public:
    static double evaluatePostfix(const std::vector<token> &tokens) ;

private:
    static double applyOperator(const std::string &op, double left, double right) ;

    static double applyFunction(const std::string &functName, double argument) ;
};

class ChrisMathParser {
public:
    static double evaluate(const std::string &input);
    std::vector<token> testfunction(const std::string &input);

private:
    Tokenizer tokenizer;
    Evaluator evaluator;
    Parser parser;
};


#endif //MATHPARSER_LIBRARY_H
